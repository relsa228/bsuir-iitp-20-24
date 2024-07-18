#ifndef TrainH
#define TrainH
#include <vcl.h>
#endif

struct Train
{
	int num;
	String date;
	String finPoint;
	float time;
	int places;

	public: static void showTrain(const Train& train, TMemo* ResultMemo)
	{
		String str;
		str = FloatToStrF(train.time, ffNumber, 4, 2);
		ResultMemo->Lines->Add("\nНомеръ рейса : " + IntToStr(train.num));
		ResultMemo->Lines->Add("\nПунктъ назначенія: " + train.finPoint);
		ResultMemo->Lines->Add("\nДата отправленія: " + train.date);
		ResultMemo->Lines->Add("\nВремя отправленія: " + str);
		ResultMemo->Lines->Add("\nСвободныхъ мъстъ: " + IntToStr(train.places));
        ResultMemo->Lines->Add("\n");
	};
};