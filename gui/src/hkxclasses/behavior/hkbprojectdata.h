#ifndef HKBPROJECTDATA_H
#define HKBPROJECTDATA_H

#include "src/hkxclasses/hkxobject.h"

class BehaviorFile;
class ProjectFile;

class hkReferencedObject;

namespace UI {
class hkbProjectStringData;

class hkbProjectData final: public HkxObject
{
    friend class ProjectFile;
public:
    hkbProjectData(HkxFile *parent, long ref = 0, hkbProjectStringData *stringdata = nullptr);
    hkbProjectData& operator=(const hkbProjectData&) = delete;
    hkbProjectData(const hkbProjectData &) = delete;
    ~hkbProjectData();
public:
    static const QString getClassname();
private:
    virtual bool readData(const HkxXmlReader & reader, long & index);
	virtual bool readData(const HkxBinaryHandler& handler, const void* object);
    bool link();
    void unlink();
    QString evaluateDataValidity();
    bool write(HkxXMLWriter *writer);
	virtual hkReferencedObject* write(HkxBinaryHandler&);
private:
    static const QStringList EventMode;
    static uint refCount;
    static const QString classname;
    hkQuadVariable worldUpWS;
    HkxSharedPtr stringData;
    QString defaultEventMode;
    mutable std::mutex mutex;
};
}
#endif // HKBPROJECTDATA_H
