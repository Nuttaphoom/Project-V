#include "TileMap.h"

void SetUV(float widthEachCell , float heightEachCell, int columnMax, int rowMax,int i,int j,int** Mapdata,
	float uvs[8]) {
	int currentColumn = Mapdata[i][j] % columnMax;
	int r = floor(Mapdata[i][j] / (float)columnMax) >= 0 ? floor(Mapdata[i][j] / (float)columnMax) : 0 ;
	int currentRow =   rowMax  - r ;

	uvs[0] = currentColumn / (columnMax * 1.0f);
	uvs[1] = currentRow  / (rowMax * 1.0f);
 
	uvs[2] = (currentColumn + 1) / (columnMax * 1.0f);
	uvs[3] = currentRow  / (rowMax * 1.0f);

	uvs[4] = (currentColumn + 1) / (columnMax * 1.0f);
	uvs[5] = (currentRow   + 1 ) / (rowMax * 1.0f);

	uvs[6] = currentColumn / (columnMax * 1.0f);
	uvs[7] = (currentRow   + 1) / (rowMax * 1.0f);
	
	/*
	uvs[0] = widthEachCell * Mapdata[i][j];
	uvs[1] = (1 - floor((float)Mapdata[i][j]  / width ) )   - (heightEachCell) ;
	printf("minus : %f\n", (1 - floor((float)Mapdata[i][j] / width)) - (heightEachCell) );
  	uvs[2] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
	uvs[3] = (1 - floor((float)Mapdata[i][j] / width)) - (heightEachCell) ;

	uvs[4] = (widthEachCell * Mapdata[i][j]) + widthEachCell;
	uvs[5] = (1 - floor((float)Mapdata[i][j] / width))  ;
	printf("%f\n", (1 - floor((float)Mapdata[i][j] / width))  );

	uvs[6] = (widthEachCell * Mapdata[i][j]);
	uvs[7] = (1 - floor((float)Mapdata[i][j] / width))   ;
	return;*/
}

TileMap::TileMap(int width, int height, int** Mapdata_Front_Layer , int** Mapdata_Middle_Layer,int **ColMapdata, string texture_path, int rowMax, int columnMax) {
	this->Map_Height = height; 
	this->Map_Width = width; 
	width -= 1;
	height -= 1;
	unsigned int texture = GameEngine::GetInstance()->GetRenderer()->LoadTexture(texture_path);


	/// Create tile in Middle Layer 
	for (int i = 0; i <  width + 1   ; i++) {
		tiles.push_back(vector<SpriteObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create every tile 
			tiles[i].push_back(new SpriteObject(texture, rowMax, columnMax));
			
			tiles[i][j]->SetAnimationLoop(0, 0, 0, 0,false);

			/// Set Size of each tile to 64 pixle width and height  
			tiles[i][j]->SetSize(64, -64);

			/// Set position of each tile 
			tiles[i][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 0));
			if (Mapdata_Middle_Layer[i][j] == -1)tiles[i][j]->SetPosition(glm::vec3(width * 10, height * 10, 0));

			/// Calculate UV 
			float uvs[8];

			//Need to use Mapdata[i][j] for UV 
			float widthEachCell = 1.0f / (float)columnMax;
 			float heightEachCell = 1.0f / (float)rowMax;
 			 SetUV(widthEachCell, heightEachCell, columnMax, rowMax, i, j,
					Mapdata_Middle_Layer, uvs);
			
			tiles[i][j]->SetUV(uvs);
			
		}
	}
	/// Create tile in Front Layer
	/*
		for (int i = 0; i <  width + 1   ; i++) {
			tiles.push_back(vector<SpriteObject*>());
		for (int j = 0; j < height + 1; j++) {
			/// Create every tile
			tiles[i + width + 1].push_back(new SpriteObject(texture, rowMax, columnMax));

			tiles[i + width + 1][j]->SetAnimationLoop(0, 0, 0, 0,false);

			/// Set Size of each tile to 64 pixle width and height
			tiles[i + width + 1][j]->SetSize(64, -64);

			/// Set position of each tile
			tiles[i + width + 1][j]->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 0));
			if (Mapdata_Front_Layer[i][j] == -1)tiles[i + width + 1][j]->SetPosition(glm::vec3(width * 10, height * 10, 0));

			/// Calculate UV
			float uvs[8];

			//Need to use Mapdata[i][j] for UV
			float widthEachCell = 1.0f / (float)columnMax;
			float heightEachCell = 1.0f / (float)rowMax;

			SetUV(widthEachCell, heightEachCell, width, height, i, j,
					Mapdata_Front_Layer, uvs);
			tiles[i + width + 1][j]->SetUV(uvs);
		}
	}*/

	/// Create all collision object for every tiles. 
	for (int i = 0; i < width + 1; i++) {
		for (int j = 0; j < height + 1; j++) {
			if (ColMapdata[i][j] == 1) {
				InvisibleObject* newInv = new InvisibleObject();
				newInv->SetPosition(glm::vec3(-GameEngine::GetInstance()->GetWindowWidth() / 2 + j * 64 + 32, GameEngine::GetInstance()->GetWindowHeight() / 2 - (i) * 64 - 32, 1));
				//newInv->SetPosition(glm::vec3(0, -256, 0));
				newInv->SetSize(64, 64);
				newInv->SetRender(true);
				tiles_collision.push_back(newInv);
				 
			}
		}
	}
}

TileMap::~TileMap() {
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			delete tiles[i][j];
		}
	}
}

vector<vector<SpriteObject*>> TileMap::GetTiles() {
	return tiles;
}

vector<InvisibleObject*> TileMap::GetColTiles() {
	return tiles_collision; 
}

 