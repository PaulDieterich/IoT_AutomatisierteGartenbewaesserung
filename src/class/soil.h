#include "M5Stack.h"


class Soil{
	public:
		Soil(){};
		Soil(int m){
			moisture = m;
		}
		Soil(int m, int h){
			moisture = m;
			heat = h;
		}

		int getMoisture(){return moisture;}
		String getMoistureString();
		void setMoisture(int m){moisture = m;}

		int getHeat(){return heat;}
		void setHeat(int h){heat = h;}
		void reset();
	private: 
		int moisture; 
		int heat;
};
//hGEVQyvGS-5WdjJXDp1uYWRtp2AcU0FqDeRU_LO1xZP1GlXHoEXmvlpm-4szVcRF1T06lyOwfkqNQVohK6tKMg==

//export INFLUX_TOKEN=rw8zv9CUYvwqih8NB12PcpFUNFy09pWoERYQBuRAlnAMgLn5yZJ2wK_kFjBOszPSh4WuGdr8CSIdwlxYY9sGbQ==

//telegraf --config https://us-east-1-1.aws.cloud2.influxdata.com/api/v2/telegrafs/09bbfb892bccb000