#ifndef MaleFemaleH
#define MaleFemaleH
#include <vcl.h>
#include "List.h"
#include "Result.h"
#endif


struct Human
{
	String name;
	String hobby;
	int num;
	int growth;
	int age;
	int pair;
	int gender;
	int weight;
	int fromAge;
	int toAge;
	int fromWeight;
	int toWeight;
	int fromGrowth;
	int toGrowth;

	public: static bool comparison(const Human& human1, const Human& human2)
	{
		if (human1.age >= human2.fromAge && human1.age <= human2.toAge && human2.pair!=0){}
		else
			return false;
		if (human1.weight >= human2.fromWeight && human1.age <= human2.toWeight && human2.pair!=0){}
		else
			return false;
		if (human1.growth >= human2.fromGrowth && human1.growth <= human2.toGrowth && human2.pair!=0){}
		else
			return false;
		if (human2.age >= human1.fromAge && human2.age <= human1.toAge && human2.pair!=0){}
		else
			return false;
		if (human2.weight >= human1.fromWeight && human2.age <= human1.toWeight && human2.pair!=0){}
		else
			return false;
		if (human2.growth >= human1.fromGrowth && human2.growth <= human1.toGrowth && human2.pair!=0)
			return true;
		else
			return false;
	};

	public: static void showElem(const Human& questionnarie, TMemo* ResultMemo)
	{
		ResultMemo->Lines->Add("\nНомер анкеты: " + IntToStr(questionnarie.num));
		ResultMemo->Lines->Add("\nИмя: " + questionnarie.name);
		ResultMemo->Lines->Add("\nВозраст: " + IntToStr(questionnarie.age));
		ResultMemo->Lines->Add("\nРост: " + IntToStr(questionnarie.growth));
		ResultMemo->Lines->Add("\nВес: " + IntToStr(questionnarie.weight));
		ResultMemo->Lines->Add("\nХобби: " + questionnarie.hobby);
	};

	public: static bool check(const Human& human)
	{
		if (human.fromAge <= human.toAge) {}
		else
			return false;
		if (human.fromGrowth <= human.toGrowth) {}
		else
			return false;
		if (human.fromWeight <= human.toWeight)
			return true;
		else
			return false;
	};

	public: static void WriteInFile(TFileStream *questF, Human questionnarie)
	{
		questF->Seek(questF->Size, 0);

		AnsiString strNum = IntToStr(questionnarie.num);
		questF->Write(strNum.c_str(), strNum.Length());

		AnsiString strGender = "\n"+IntToStr(questionnarie.gender);
		questF->Write(strGender.c_str(), strGender.Length());

		AnsiString strPair = "\n"+IntToStr(questionnarie.pair);
		questF->Write(strPair.c_str(), strPair.Length());

		AnsiString strName = "\n"+questionnarie.name;
		questF->Write(strName.c_str(), strName.Length());

		AnsiString strAge = "\n"+IntToStr(questionnarie.age);
		questF->Write(strAge.c_str(), strAge.Length());

		AnsiString strFromAge = "\n"+IntToStr(questionnarie.fromAge);
		questF->Write(strFromAge.c_str(), strFromAge.Length());

		AnsiString strToAge = "\n"+IntToStr(questionnarie.toAge);
		questF->Write(strToAge.c_str(), strToAge.Length());

		AnsiString strGrowth = "\n"+IntToStr(questionnarie.growth);
		questF->Write(strGrowth.c_str(), strGrowth.Length());

		AnsiString strFromGrowth = "\n"+IntToStr(questionnarie.fromGrowth);
		questF->Write(strFromGrowth.c_str(), strFromGrowth.Length());

		AnsiString strToGrowth = "\n"+IntToStr(questionnarie.toGrowth);
		questF->Write(strToGrowth.c_str(), strToGrowth.Length());

		AnsiString strWeight = "\n"+IntToStr(questionnarie.weight);
		questF->Write(strWeight.c_str(), strWeight.Length());

		AnsiString strFromWeight = "\n"+IntToStr(questionnarie.fromWeight);
		questF->Write(strFromWeight.c_str(), strFromWeight.Length());

		AnsiString strToWeight = "\n"+IntToStr(questionnarie.toWeight);
		questF->Write(strToWeight.c_str(), strToWeight.Length());

		AnsiString strHobby = "\n"+questionnarie.hobby+"\n";
		questF->Write(strHobby.c_str(), strHobby.Length());
	};
};
