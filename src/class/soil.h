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
		void setMoisture(int m){moisture = m;}

		int getHeat(){return heat;}
		void setHeat(int h){heat = h;}
		void reset();
	private: 
		int moisture; 
		int heat;
};
