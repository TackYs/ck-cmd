#ifndef CHARACTERFILE_H
#define CHARACTERFILE_H

#include "src/filetypes/hkxfile.h"

class SkeletonFile;
class ProjectFile;
class SkyrimAnimationMotionData;


namespace UI{
	class hkbCharacterData;
	class hkbBoneWeightArray;
	class hkaSkeleton;
}

class CharacterFile final: public HkxFile
{
    friend class ProjectFile;
public:
    CharacterFile(MainWindow *window, ProjectFile *projectfile, const QString & name, bool autogeneratedata = false, const QString & skeletonrelativepath = "");
    CharacterFile& operator=(const CharacterFile&) = delete;
    CharacterFile(const CharacterFile &) = delete;
    ~CharacterFile();
public:
    bool addObjectToFile(UI::HkxObject *obj, long ref = -1);
    QString getSkeletonFileName() const;
    QString getRootObjectReferenceString();
    QString getBehaviorDirectoryName() const;
    QString getRigName() const;
    QStringList getRigBoneNames() const;
    int getNumberOfBones(bool ragdoll = false) const;
    QString getRagdollName() const;
    QStringList getRagdollBoneNames() const;
    QStringList getAnimationNames() const;
    QString getAnimationNameAt(int index) const;
    QString getCharacterPropertyNameAt(int index) const;
    int getCharacterPropertyIndex(const QString & name) const;
    QStringList getCharacterPropertyNames() const;
    QStringList getCharacterPropertyTypenames() const;
	UI::hkVariableType getCharacterPropertyTypeAt(int index) const;
    int getAnimationIndex(const QString & name) const;
    int getNumberOfAnimations() const;
    bool isAnimationUsed(const QString & animationname) const;
    QString getRootBehaviorFilename() const;
    void getCharacterPropertyBoneWeightArray(const QString &name, UI::hkbBoneWeightArray *ptrtosetdata) const;
    bool merge(CharacterFile *recessivefile);
	UI::HkxSharedPtr& getCharacterPropertyValues();
	UI::HkxSharedPtr& getFootIkDriverInfo();
	UI::HkxSharedPtr& getHandIkDriverInfo();
	UI::HkxSharedPtr& getStringData();
	UI::HkxSharedPtr& getMirroredSkeletonInfo();
    bool appendAnimation(SkyrimAnimationMotionData *motiondata);
    SkyrimAnimationMotionData getAnimationMotionData(int animationindex) const;
	UI::HkxSharedPtr * findCharacterPropertyValues(long ref);
	UI::HkxSharedPtr * findCharacterData(long ref);
    void setSkeletonFile(SkeletonFile *skel);
	bool parseBinary();
    bool parse();
    void write();
    QStringList getLocalFrameNames() const;
	UI::HkxObject * getCharacterStringData() const;
    UI::hkaSkeleton * getSkeleton(bool isragdoll = false) const;
protected:
    bool link();
private:
    void addAnimation(const QString & name);
	UI::hkbBoneWeightArray * addNewBoneWeightArray();
	UI::hkbCharacterData * getCharacterData() const;
    void addFootIK();
    void addHandIK();
    void disableFootIK();
    void disableHandIK();
private:
    ProjectFile *project;
    SkeletonFile *skeleton;
	UI::HkxSharedPtr characterData;
	UI::HkxSharedPtr characterPropertyValues;
	UI::HkxSharedPtr footIkDriverInfo;
	UI::HkxSharedPtr handIkDriverInfo;
	UI::HkxSharedPtr stringData;
	UI::HkxSharedPtr mirroredSkeletonInfo;
    QVector <UI::HkxSharedPtr> boneWeightArrays;
    long largestRef;
    mutable std::mutex mutex;
};

#endif // CHARACTERFILE_H