#include "dataparser.h"
#include "rangeset.h"
#include <QRegExp>
#include <QFile>
#include <QTextStream>

DataParser::DataParser(){
    parsedCnt = 0;
    ipr = new RangeSet<unsigned int>;//(0x00000000, 0xffffffff);
}

DataParser::~DataParser(){
    delete ipr;
}

void DataParser::parse(QIODevice *data){
    QRegExp rx("^[^0-9]{3}(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})(\\/(\\d{1,2}))?", Qt::CaseInsensitive);
    ipr->init(0x00000000, 0xffffffff);

    QTextStream ds(data);
    QString ln;
    parsedCnt = 0;
    while(!ds.atEnd()){
        ln = ds.readLine();
        if(rx.indexIn(ln) != -1){
            int ip = 0;
            ip |= rx.cap(1).toInt() << 24;
            ip |= rx.cap(2).toInt() << 16;
            ip |= rx.cap(3).toInt() << 8;
            ip |= rx.cap(4).toInt();

            int range = 1 << (32 - rx.cap(6).toInt()); //(0, range)
            range -= 1;

            ip &= range ^ 0xffffffff;

            ++parsedCnt;

            ipr->exclude(ip, ip+range);
        }
    }
}

int DataParser::resultCount() const {
    return  ipr->size();
}

int DataParser::parsedCount() const {
    return parsedCnt;
}

#define IP4_TO_STR(_a) (_a >> 24) << '.' << ((_a >> 16) & 0xFF) << '.' << ((_a >> 8) & 0xFF) << '.' << (_a & 0xFF)
bool DataParser::flushToFile(const QString &name) const {
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    RangeSet<unsigned int>::const_iterator i;
    for(i = ipr->begin(); i != ipr->end(); ++i){
        out << IP4_TO_STR(i->first) << " - " << IP4_TO_STR(i->second) << endl;
    }

    return true;
}
