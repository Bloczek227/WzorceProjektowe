#ifndef WP_PROJ_INTERFACES_H
#define WP_PROJ_INTERFACES_H

class Item;
class Champion;
class Skill;
class ItemSkill;
class ItemSkillsSubject;
class DotHandler;
class ItemSkillsSubjectInterface;

class ChampionLevelInterface{
public:
    virtual int lv() const=0;
    virtual int Q_level() const=0;
    virtual int W_level() const=0;
    virtual int E_level() const=0;
    virtual int R_level() const=0;
};


class ChampionPhysicalStatsInterface{
public:
    virtual double baseADLv1()=0;
    virtual double ADPerLevel()=0;
    virtual double baseCriticalDamage()=0;
    virtual double baseAD()=0;
    virtual double ad() const=0;
    virtual double criticalChance() const=0;
    virtual double criticalDamage() const=0;
    virtual double lethality() const=0;
    virtual double percentageArmorPenetration() const=0;
    virtual double physicalDamageMultiplier() const=0;
    virtual double trueDamageMultiplier() const=0;
    virtual double damageMultiplier() const=0;
    virtual void setAD(double val)=0;
    virtual void setCriticalChance(double val)=0;
    virtual void setCriticalDamage(double val)=0;
    virtual void setLethality(double val)=0;
    virtual void setPercentageArmorPenetration(double val)=0;
    virtual void setPhysicalDamageMultiplier(double val)=0;
    virtual void setTrueDamageMultiplier(double val)=0;
    virtual void setDamageMultiplier(double val)=0;
};


class ChampionMagicStatsInterface{
public:
    virtual double flatAP() const=0;
    virtual double apMultiplier() const=0;
    virtual double flatMagicPenetration() const=0;
    virtual double percentageMagicPenetration() const=0;
    virtual double ap() const=0;
    virtual double magicDamageMultiplier() const=0;
    virtual void setFlatAP(double val)=0;
    virtual void setAPMultiplier(double val)=0;
    virtual void setFlatMagicPenetration(double val)=0;
    virtual void setPercentageMagicPenetration(double val)=0;
    virtual void setMagicDamageMultiplier(double val)=0;
};

class ChampionDefensiveStatsInterface{
public:
    virtual double baseHPLv1()=0;
    virtual double HPPerLevel()=0;
    virtual double baseArmorLv1()=0;
    virtual double ArmorPerLevel()=0;
    virtual double baseMRLv1()=0;
    virtual double MRPerLevel()=0;
    virtual double baseHP()=0;
    virtual double baseArmor()=0;
    virtual double baseMR()=0;
    virtual double maxHP() const=0;
    virtual double armor() const=0;
    virtual double magicResist() const=0;
    virtual double currHP() const=0;
    virtual void setMaxHP(double val)=0;
    virtual void setArmor(double val)=0;
    virtual void setMagicResist(double val)=0;
    virtual void setCurrHP(double val)=0;
};

class ChampionInterface: public ChampionLevelInterface, public ChampionPhysicalStatsInterface,
                         public ChampionMagicStatsInterface,public ChampionDefensiveStatsInterface{
public:
    virtual ItemSkillsSubjectInterface* getItemSkillsSubject() const=0;
    virtual DotHandler* getDotHandler() const=0;
    virtual void addBaseStats(Champion* derived)=0;
    virtual void receiveDamage(Skill* skill, ChampionInterface* offensive_champion)=0;
};

class ItemSkillsSubjectInterface{
public:
    virtual void before_use(Skill* skill, ChampionInterface* championInterface)=0;
    virtual void after_use(Skill* skill, ChampionInterface* championInterface)=0;
    virtual void add(ItemSkill* skill)=0;
};

#endif //WP_PROJ_INTERFACES_H
