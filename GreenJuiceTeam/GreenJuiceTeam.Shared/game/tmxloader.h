#ifndef TMXLOADER_H
#define TMXLOADER_H

#include <string>
#include <vector>

#include "core/gl2d.h"

using namespace std;

class TMXLoader
{
    public:
		class FloorBreakingAnimation
		{
			public:
				int x;
				int y;
				int currentFrame;
				bool active;
		};

		TMXLoader();
        ~TMXLoader();


        void cleanup();

		void changeTile(int x, int y, int value);
		void breakFloor(int x, int y);
		bool isPassable(int x, int y);
		bool isKey(int x, int y);
		bool isDoor(int x, int y);
		bool isHole(int x, int y);

		void paint();

        bool loadDocument();
		bool keyOnMap;

	


    protected:

    private:
         vector< int >  m_LayerData;

		void decode_and_store_map_data();

        void buildMapImage();

		glImage tileset[25];	
		glImage keyset[25];	
		glImage doorset[5];	
		glImage pisoquebrando[5];

		static const int cols;
		static const int rows;
		vector<FloorBreakingAnimation*> floorAnimations;		

		int frames;
		int keyFrame;
		int doorFrame;
       

};

#endif 
