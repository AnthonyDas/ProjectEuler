#include <iostream> 
#include <string> 

#include "logger.h"
#include "prime_helper.h"

#include "Q001Q010.h"
#include "Q011Q020.h" 
#include "Q021Q030.h" 
#include "Q031Q040.h" 
#include "Q041Q050.h" 
#include "Q051Q060.h" 
#include "Q061Q070.h"
#include "Q071Q080.h"
#include "Q081Q090.h"
#include "Q091Q100.h"

#include "Q101Q110.h"
#include "Q111Q120.h"
#include "Q121Q130.h"
#include "Q131Q140.h"
#include "Q141Q150.h"
#include "Q151Q160.h"
#include "Q161Q170.h"
#include "Q171Q180.h"
#include "Q181Q190.h"
#include "Q191Q200.h"

#include "Q201Q210.h"
#include "Q211Q220.h"

#include "Q231Q240.h"
#include "Q241Q250.h"

#include "Q351Q360.h"
#include "Q381Q390.h"

#include "Q401Q410.h"

#include "Q491Q500.h"
#include "Q501Q510.h"

//---------------------------------------------------------------
// Copyright © (2016) Anthony Das
//---------------------------------------------------------------
// https://projecteuler.net

int problem_count = 0,  problem_err_count = 0;

template <typename T>
void runProblem(std::string problemId, const T &actual, const T &expected) {
	++problem_count;
	if (actual == expected) {
		LOG_INF(problemId + ": Success");
	} else {
		std::ostringstream stringstream;
		stringstream << problemId << ": Actual [" << actual << "] Expected [" << expected << "]";
		LOG_ERR(stringstream.str());

		++problem_err_count;
	}
}


int main() {
	// standard_out_logger::create();
	standard_out_and_file_logger::create("C:\\OneDrive\\Git\\ProjectEuler\\ProjectEuler\\ProjectEuler.log");

	runProblem("147", q147(), 0LL);
	
	// runProblem("186", q186(), 0);

	/*
	runProblem("1", q1(), 233168);
	runProblem("1 quick", q1_quick(), 233168);
	runProblem("2", q2(), 4613732);
	runProblem("2 quick", q2_quick(), 4613732);
	runProblem("3", q3(), 6857LL); // LL - long long int
	runProblem("3 quick", q3_quick(), 6857LL);
	runProblem("4", q4(), 906609);
	runProblem("5", q5(), 232792560LL);
	runProblem("6", q6(), 25164150LL);
	runProblem("6 quick", q6_quick(), 25164150LL);
	runProblem("7", q7(), 104743);
	runProblem("8", q8(), 23514624000);
	runProblem("9", q9(), 31875000);
	runProblem("10", q10(), 142913828922LL);
	runProblem("10 quick", q10_quick(), 142913828922LL);

	runProblem("11", q11(), 70600674);
	runProblem("12", q12(), 76576500);
	runProblem("13", q13(), 5537376230);
	runProblem("14", q14(), 837799);
	runProblem("15", q15(), 137846528820);
	runProblem("16", q16(), 1366);
	runProblem("17", q17(), 21124);
	runProblem("18", q18(), 1074);
	runProblem("19", q19(), 171);
	runProblem("20", q20(), 648);

	runProblem("21", q21(), 31626);
	runProblem("22", q22(), 871198282);
	runProblem("23", q23(), 4179871U); // U - unsigned
	runProblem("24", q24(), std::string("2783915460"));
	runProblem("25", q25(), 4782); 
	runProblem("26", q26(), 983);
	runProblem("27", q27(), -59231);
	runProblem("28", q28(), 669171001);
	runProblem("29", q29(), 9183);
	runProblem("30", q30(), 443839);
	
	runProblem("31", q31(), 73682);
	runProblem("32", q32(), 45228);
	runProblem("33", q33(), 100);
	runProblem("34", q34(), 40730);
	runProblem("35", q35(), 55);
	runProblem("36", q36(), 872187);
	runProblem("37", q37(), 748317LL);
	runProblem("38", q38(), 932718654LL);
	runProblem("39", q39(), 840);
	runProblem("40", q40(), 210); 

	runProblem("41", q41(), 7652413); 
	runProblem("42", q42(), 162);
	runProblem("43", q43(), 16695334890);
	runProblem("44", q44(), 5482660);
	runProblem("45", q45(), 1533776805LL);
	runProblem("46", q46(), 5777);
	runProblem("47", q47(), 134043);
	runProblem("48", q48(), 9110846700ULL);
	runProblem("49", q49(), 296962999629);
	runProblem("50", q50(), 997651); 
	
	runProblem("51", q51(), 121313);
	runProblem("52", q52(), 142857);
	runProblem("53", q53(), 4075);
	runProblem("54", q54(), 376);
	runProblem("55", q55(), 249);
	runProblem("56", q56(), 972);
	runProblem("57", q57(), 153);
	runProblem("58", q58(), 26241LL);
	runProblem("59", q59(), 107359);
	runProblem("60", q60(), 26033);

	runProblem("61", q61(), 28684);
	runProblem("62", q62(), 127035954683);
	runProblem("63", q63(), 49);
	runProblem("64", q64(), 1322);
	runProblem("65", q65(), 272);
	// runProblem("66", q66(), 0);
	runProblem("67", q67(), 7273);
	runProblem("68", q68(), 6531031914842725);
	runProblem("69", q69(), 510510);
	runProblem("70", q70(), 8319823);

	runProblem("71", q71(), 428570);
	runProblem("72", q72(), 303963552391LL);
	runProblem("73", q73(), 7295372);
	runProblem("74", q74(), 402); // Performance
	runProblem("75", q75(), 161667);
	runProblem("76", q76(), 190569291);
	runProblem("77", q77(), 71);
	// runProblem("78", q78(), 0LL);
	runProblem("79", q79(), 73162890); // Performance: 4mins Visual Studio, 3secs g++ compiled

	runProblem("81", q81(), 427337); 
	runProblem("82", q82(), 260324);
	runProblem("83", q83(), 425185);
	runProblem("84", q84(), std::string("101524")); // Still need to implement rolling three doubles
	runProblem("85", q85(), 2772);

	runProblem("86", q86(), 1818);
	runProblem("87", q87(), 1097343);
	runProblem("89", q89(), 743);
	runProblem("90", q90(), 1217);

	runProblem("91", q91(), 14234);
	runProblem("92", q92(), 8581146);
	runProblem("94", q94(), 518408346);
	runProblem("95", q95(), 14316);
	runProblem("96", q96(), 24702);
	runProblem("97", q97(), 8739992577);

	runProblem("99", q99(), 709);
	runProblem("100", q100(), 756872327473LL); // Deriving the closed formula https://oeis.org/A011900

	runProblem("102", q102(), 228);
	runProblem("104", q104(), 329468);

	runProblem("107", q107(), 259679);

	runProblem("109", q109(), 38182);
	
	runProblem("112", q112(), 1587000);
	runProblem("113", q113(), 51161058134250);
	runProblem("114", q114(), 16475640049);
	runProblem("115", q115(), 168);
	runProblem("116", q116(), 20492570929);
	runProblem("117", q117(), 100808458960497);
	// runProblem("118", q118(), 0);
	runProblem("119", q119(), 248155780267521);

	runProblem("124", q124(), 21417);
	runProblem("125", q125(), 2906969179LL);
	// runProblem("127", q127(), 0LL);

	runProblem("129", q129(), 1000023);
	runProblem("130", q130(), 149253);
	runProblem("131", q131(), 173);
	runProblem("145", q145(), 608720);
	
	runProblem("151", q151(), round(0.46439878160109455 * 1000000) / 1000000); // 6 d.p.
	runProblem("155", q155(), 3'857'447);

	runProblem("162", q162(), std::string("3D58725572C62302"));
	runProblem("166", q166(), 7130034);

	runProblem("172", q172(), 227485267000992000);
	runProblem("173", q173(), 1572729);
	runProblem("174", q174(), 209566);

	runProblem("179", q179(), 986262);


	runProblem("187", q187(), 17427258);
	runProblem("189", q189(), 10834893628237824);

	runProblem("191", q191(), 1918080160);

	runProblem("204", q204(), 2944730);
	runProblem("205", q205(), round(0.57314407678298018 * 10000000) / 10000000); // 7 d.p.
	runProblem("206", q206(), 1389019170LL);

	runProblem("214", q214(), 1677366278943); // Performance: Visual Studio, 20secs g++ compiled
	runProblem("215", q215(), 806844323190414); // Performance: Visual Studio, 120secs g++ compiled

	runProblem("231", q231(), 7526965179680);

	runProblem("243", q243(), 892371480LL);

	runProblem("357", q357(), 1739023853137LL);
	// runProblem("381", q381(), 0LL);

	// runProblem("387", q387(), 0LL);

	// runProblem("407", q407(), 0LL);

	// runProblem("500", q500(), 0LL);

	runProblem("504", q504(), 694687); // Performance: Visual Studio, 20secs g++ compiled
	*/

	if (problem_err_count == 0) {
		std::ostringstream stringstream;
		stringstream << "No failures detected. Run: " << problem_count;
		LOG_INF(stringstream.str());
	}
	else {
		std::ostringstream stringstream;
		stringstream << "Failures detected. Run: " << problem_count << ", Fails:" << problem_err_count;
		LOG_ERR(stringstream.str());
	}

	std::cout << "Finished - type something to quit" << std::endl;
	int dummy; std::cin >> dummy;
	return 0;
}