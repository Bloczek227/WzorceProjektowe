#ifndef WP_PROJ_INTERFACES_H
#define WP_PROJ_INTERFACES_H

class Item;
template<typename T>
concept ItemConcept=std::derived_from<T,Item>;
class Champion;
template<typename T>
concept ChampionConcept=std::derived_from<T,Champion>;

class Skill;
class ItemSkill;
class ItemSkillsObservers;
class DotHandler;
class ItemSkillsObserversInterface;

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
};


class ChampionMagicStatsInterface{
public:
    virtual double flatAP() const=0;
    virtual double apMultiplier() const=0;
    virtual double flatMagicPenetration() const=0;
    virtual double percentageMagicPenetration() const=0;
    virtual double ap() const=0;
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
};

class ChampionInterface: public ChampionLevelInterface, public ChampionPhysicalStatsInterface,
                         public ChampionMagicStatsInterface,public ChampionDefensiveStatsInterface{
public:
    virtual ItemSkillsObserversInterface* getItemSkillsObservers() const=0;
    virtual DotHandler* getDotHandler() const=0;
    virtual void addBaseStats(Champion* derived)=0;
    virtual void receiveDamage(Skill* skill, ChampionInterface* offensive_champion)=0;
};

class ItemSkillsObserversInterface{
public:
    virtual void before_use(Skill* skill, ChampionInterface* championInterface)=0;
    virtual void after_use(Skill* skill, ChampionInterface* championInterface)=0;
    virtual void add(ItemSkill* skill)=0;
};

#endif //WP_PROJ_INTERFACES_H
