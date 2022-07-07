#include <vector>
#include <iostream>
#include "Cubo.h"
//#include "Matrices.h"

using namespace std;

void change(int& a, int& b, int& c, int& d) {
	int t = a;
	a = b;
	b = c;
	c = d;
	d = t;
}

class cuboRubik {
	vector<int> cOri;
	vector<int> eOri;
public:
	vector<cubo*> Cubos;
	vector<vector<float>> centros{
		//Front
		{-0.5f, 0.5f, 0.5f}, //0  ufl
		{ 0.0f, 0.5f, 0.5f}, //1  uf
		{ 0.5f, 0.5f, 0.5f}, //2  urf
		{-0.5f, 0.0f, 0.5f}, //3  fl  
		{ 0.0f, 0.0f, 0.5f}, //4  RED
		{ 0.5f, 0.0f, 0.5f}, //5  fr
		{-0.5f, -0.5f, 0.5f}, //6 dlf
		{ 0.0f, -0.5f, 0.5f}, //7 df
		{ 0.5f, -0.5f, 0.5f}, //8 dfr
		//Mid
		{-0.5f, 0.5f, 0.0f}, //9  ul
		{ 0.0f, 0.5f, 0.0f}, //10 BLUE
		{ 0.5f, 0.5f, 0.0f}, //11 ur
		{-0.5f, 0.0f, 0.0f}, //12  WHITE
		//{ 0.0f, 0.0f, 0.0f}, //13
		{ 0.5f, 0.0f, 0.0f}, //13 YELLOW
		{-0.5f, -0.5f, 0.0f}, //14  dl
		{ 0.0f, -0.5f, 0.0f}, //15 GREEN
		{ 0.5f, -0.5f, 0.0f}, //16  dr
		 //Back
		{-0.5f, 0.5f, -0.5f}, //17  ulb
		{ 0.0f, 0.5f, -0.5f}, //18  ub
		{ 0.5f, 0.5f, -0.5f}, //19 ubr
		{-0.5f, 0.0f, -0.5f}, //20  bl
		{ 0.0f, 0.0f, -0.5f}, //21 ORANGE
		{ 0.5f, 0.0f, -0.5f}, //22  br
		{-0.5f, -0.5f, -0.5f}, //23  dbl
		{ 0.0f, -0.5f, -0.5f}, //24  db
		{ 0.5f, -0.5f, -0.5f} //25  drb
	};
	vector<vector<int>> texIndex{
		//Front
		{1,0,52,0,0,21}, //0
		{2,0,53,0,0,0}, //1
		{3,0,54,0,37,0}, //2
		{4,0,0,0,0,24}, //3
		{5,0,0,0,0,0}, //4
		{6,0,0,0,40,0}, //5
		{7,0,0,28,0,27}, //6
		{8,0,0,29,0,0}, //7
		{9,0,0,30,43,0}, //8
		//Mid
		{0,0,49,0,0,20}, //9
		{0,0,50,0,0,0}, //10
		{0,0,51,0,38,0}, //11
		{0,0,0,0,0,23}, //12
		//{0,0,0,0,0,0}, //13
		{0,0,0,0,41,0}, //14
		{0,0,0,31,0,26}, //15
		{0,0,0,32,0,0}, //16
		{0,0,0,33,44,0}, //17
		 //Back
		{0,16,46,0,0,19}, //18
		{0,17,47,0,0,0}, //19
		{0,18,48,0,39,0}, //20
		{0,13,0,0,0,22}, //21
		{0,14,0,0,0,0}, //22
		{0,15,0,0,42,0}, //23
		{0,10,0,34,0,25}, //24
		{0,11,0,35,0,0}, //25
		{0,12,0,36,45,0}, //26
	};
	vector<vector<int>> flipIndex{
		//Front
		{0,0,0,0,0,0}, //0
		{0,0,0,0,0,0}, //1
		{0,0,0,0,0,0}, //2
		{0,0,0,0,0,0}, //3
		{0,0,0,0,0,0}, //4
		{0,0,0,0,0,0}, //5
		{0,0,0,1,0,0}, //6
		{0,0,0,1,0,0}, //7
		{0,0,0,1,0,0}, //8
		//Mid
		{0,0,0,0,0,0}, //9
		{0,0,0,0,0,0}, //10
		{0,0,0,0,0,0}, //11
		{0,0,0,0,0,0}, //12
		//{0,0,0,0,0,0}, //13
		{0,0,0,0,0,0}, //14
		{0,0,0,1,0,0}, //15
		{0,0,0,1,0,0}, //16
		{0,0,0,1,0,0}, //17
		 //Back
		{0,1,0,0,0,0}, //18
		{0,1,0,0,0,0}, //19
		{0,1,0,0,0,0}, //20
		{0,1,0,0,0,0}, //21
		{0,1,0,0,0,0}, //22
		{0,1,0,0,0,0}, //23
		{0,1,0,1,0,0}, //24
		{0,1,0,1,0,0}, //25
		{0,1,0,1,0,0}, //26
	};
	
	enum corner { ufl, urf, dlf, dfr, ulb, ubr, dbl, drb }; //0-8
	enum edge { uf, fl, fr, df, ul, ur, dl, dr, ub, bl, br, db };//0-10

	vector< vector<corner>> camadasC{
		{ufl,urf,dlf,dfr}, //F
		{ulb,ubr,dbl,drb}, //B
		{ufl,urf,ulb,ubr}, //U
		{dlf,dfr,dbl,drb}, //D
		{urf,dfr,ubr,drb}, //R
		{ufl,dlf,ulb,dbl}  //L
	};
	vector< vector<edge>> camadasE{
		{uf,fl,fr,df}, //F
		{ub,bl,br,db}, //B
		{uf,ul,ur,ub}, //U
		{df,dl,dr,db}, //D
		{fr,ur,dr,br}, //R
		{fl,ul,dl,bl}  //L
	};

	cuboRubik();
	void init(Shader OurShader);
	void draw(Shader OurShader);
	void draw(Shader OurShader, vector<glm::vec3> positions);
	void drawA(Shader OurShader, vector<glm::vec3> positions, glm::vec3 vec);
	void deleteCubo();
	cuboRubik::~cuboRubik() {
		cout << "Why\n";
	}

	void Up(Shader Ourshader, bool p);
	void Down(bool p);
	void Rigth(bool p);
	void Left(bool p);
	void Front(bool p);
	void Back(bool p);
	
	void Up2(bool p);
	void Down2(bool p);
	void Rigth2(bool p);
	void Left2(bool p);
	void Front2(bool p);
	void Back2(bool p);
	
};

cuboRubik::cuboRubik() {
	cOri = { 0,2,6,8,17,19,23,25 };
	eOri = { 1,3,5,7,9,11,14,16,18,20,22,24 };
	
	for (int j = 0; j < centros.size(); j++) {
		Cubos.push_back(new cubo(centros[j][0], centros[j][1], centros[j][2], 0.40f, texIndex[j], flipIndex[j], j));
	}
}

void cuboRubik::init(Shader OurShader) {
	for (auto i : Cubos) {
		i->init(OurShader);
	}

	//Cubos[0]->printVertices(0);
}

void cuboRubik::draw(Shader Ourshader, vector<glm::vec3> positions) {
	Ourshader.use();
	for (auto i : Cubos) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i->index]);
		Ourshader.setMat4("model", model);
		i->draw();
	}
}
//test-------------------------------------------------------------
void cuboRubik::drawA(Shader Ourshader, vector<glm::vec3> positions, glm::vec3 vec) {
	Ourshader.use();
	for (auto i : Cubos) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i->idCenter]);
		model = glm::scale(model, vec);
		Ourshader.setMat4("model", model);
		i->draw();
	}
}

void cuboRubik::draw(Shader Ourshader) {
	Ourshader.use();
	for (auto i : Cubos) {
		glm::mat4 model = glm::mat4(1.0f);
		Ourshader.setMat4("model", model);
		i->draw();
	}
}

void cuboRubik::deleteCubo() {
	for (auto i : Cubos) {
		i->deleteCaras();
	}
}

void cuboRubik::Up(Shader Ourshader, bool p) {
	if (!p) {
		Cubos[10]->rotar(Ry2); // BLUE
		for (int i = 0; i < camadasC[2].size(); i++) {
			//cout << "camadas: " << camadasC[2][i] << "  " << i << ": " << cOri[camadasC[2][i]] << " , ";
			//glm::mat4 model = glm::mat4(1.0f);
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, -1.0f, 0.0f));
			//Ourshader.setMat4("model", model);
			//Cubos[cOri[camadasC[2][i]]]->draw();
			Cubos[cOri[camadasC[2][i]]]->rotar(Ry2);
		}
		for (int i = 0; i < camadasE[2].size(); i++) {
			Cubos[eOri[camadasE[2][i]]]->rotar(Ry2);
		}
	}
	else {

		change(Cubos[cOri[urf]]->idCenter, Cubos[cOri[ufl]]->idCenter, Cubos[cOri[ulb]]->idCenter, Cubos[cOri[ubr]]->idCenter);
		int tOri = cOri[urf];
		cOri[urf] = cOri[ubr];
		cOri[ubr] = cOri[ulb];
		cOri[ulb] = cOri[ufl];
		cOri[ufl] = tOri;
		
		change(Cubos[eOri[ub]]->idCenter, Cubos[eOri[ur]]->idCenter, Cubos[eOri[uf]]->idCenter, Cubos[eOri[ul]]->idCenter);
		tOri = eOri[ub];
		eOri[ub] = eOri[ul];
		eOri[ul] = eOri[uf];
		eOri[uf] = eOri[ur];
		eOri[ur] = tOri;
		
	}
}

void cuboRubik::Up2(bool p) {
	if (!p) {
		Cubos[10]->rotar(Ry); // BLUE
		for (int i = 0; i < camadasC[2].size(); i++) {
			Cubos[cOri[camadasC[2][i]]]->rotar(Ry);
		}
		for (int i = 0; i < camadasE[2].size(); i++) {
			Cubos[eOri[camadasE[2][i]]]->rotar(Ry);
		}
	}
	else {
		change(Cubos[cOri[ufl]]->idCenter, Cubos[cOri[urf]]->idCenter, Cubos[cOri[ubr]]->idCenter, Cubos[cOri[ulb]]->idCenter);
		int tOri = cOri[ufl];
		cOri[ufl] = cOri[ulb];
		cOri[ulb] = cOri[ubr];
		cOri[ubr] = cOri[urf];
		cOri[urf] = tOri;

		change(Cubos[eOri[ur]]->idCenter, Cubos[eOri[ub]]->idCenter, Cubos[eOri[ul]]->idCenter, Cubos[eOri[uf]]->idCenter);
		tOri = eOri[ur];
		eOri[ur] = eOri[uf];
		eOri[uf] = eOri[ul];
		eOri[ul] = eOri[ub];
		eOri[ub] = tOri;
	}
}

void cuboRubik::Down(bool p) {
	if (!p) {
		Cubos[15]->rotar(Ry); // GREEN
		for (int i = 0; i < camadasC[3].size(); i++) {
			//cout << "camadas: " << camadasC[3][i] << "  " << i << ": " << cOri[camadasC[3][i]] << " , ";
			Cubos[cOri[camadasC[3][i]]]->rotar(Ry);
		}
		for (int i = 0; i < camadasE[3].size(); i++) {
			Cubos[eOri[camadasE[3][i]]]->rotar(Ry);
		}
	}
	else {
		change(Cubos[cOri[dfr]]->idCenter, Cubos[cOri[drb]]->idCenter, Cubos[cOri[dbl]]->idCenter, Cubos[cOri[dlf]]->idCenter);
		char tOri = cOri[dfr];
		cOri[dfr] = cOri[dlf];
		cOri[dlf] = cOri[dbl];
		cOri[dbl] = cOri[drb];
		cOri[drb] = tOri;

		change(Cubos[eOri[df]]->idCenter, Cubos[eOri[dr]]->idCenter, Cubos[eOri[db]]->idCenter, Cubos[eOri[dl]]->idCenter);
		tOri = eOri[df];
		eOri[df] = eOri[dl];
		eOri[dl] = eOri[db];
		eOri[db] = eOri[dr];
		eOri[dr] = tOri;
	}

}

void cuboRubik::Down2(bool p) {
	if (!p) {
		Cubos[15]->rotar(Ry2); // GREEN
		for (int i = 0; i < camadasC[3].size(); i++) {
			Cubos[cOri[camadasC[3][i]]]->rotar(Ry2);
		}
		for (int i = 0; i < camadasE[3].size(); i++) {
			Cubos[eOri[camadasE[3][i]]]->rotar(Ry2);
		}
	}
	else {
		change(Cubos[cOri[drb]]->idCenter, Cubos[cOri[dfr]]->idCenter, Cubos[cOri[dlf]]->idCenter, Cubos[cOri[dbl]]->idCenter);
		char tOri = cOri[drb];
		cOri[drb] = cOri[dbl];
		cOri[dbl] = cOri[dlf];
		cOri[dlf] = cOri[dfr];
		cOri[dfr] = tOri;

		change(Cubos[eOri[dr]]->idCenter, Cubos[eOri[df]]->idCenter, Cubos[eOri[dl]]->idCenter, Cubos[eOri[db]]->idCenter);
		tOri = eOri[dr];
		eOri[dr] = eOri[db];
		eOri[db] = eOri[dl];
		eOri[dl] = eOri[df];
		eOri[df] = tOri;
	}
}

void cuboRubik::Rigth(bool p) {

	if (!p) {
		Cubos[13]->rotar(Rx2); // YELL
		for (int i = 0; i < camadasC[4].size(); i++) {
			Cubos[cOri[camadasC[4][i]]]->rotar(Rx2);
		}
		for (int i = 0; i < camadasE[4].size(); i++) {
			Cubos[eOri[camadasE[4][i]]]->rotar(Rx2);
		}
	}
	else {
		change(Cubos[cOri[urf]]->idCenter, Cubos[cOri[ubr]]->idCenter, Cubos[cOri[drb]]->idCenter, Cubos[cOri[dfr]]->idCenter);
		char tOri = cOri[urf];
		cOri[urf] = cOri[dfr];
		cOri[dfr] = cOri[drb];
		cOri[drb] = cOri[ubr];
		cOri[ubr] = tOri;

		change(Cubos[eOri[fr]]->idCenter, Cubos[eOri[ur]]->idCenter, Cubos[eOri[br]]->idCenter, Cubos[eOri[dr]]->idCenter);
		tOri = eOri[fr];
		eOri[fr] = eOri[dr];
		eOri[dr] = eOri[br];
		eOri[br] = eOri[ur];
		eOri[ur] = tOri;
	}
}

void cuboRubik::Rigth2(bool p) {
	if (!p) {
		Cubos[13]->rotar(Rx); // YELL
		for (int i = 0; i < camadasC[4].size(); i++) {
			Cubos[cOri[camadasC[4][i]]]->rotar(Rx);
		}
		for (int i = 0; i < camadasE[4].size(); i++) {
			Cubos[eOri[camadasE[4][i]]]->rotar(Rx);
		}
	}
	else {
		change(Cubos[cOri[ubr]]->idCenter, Cubos[cOri[urf]]->idCenter, Cubos[cOri[dfr]]->idCenter, Cubos[cOri[drb]]->idCenter);
		char tOri = cOri[ubr];
		cOri[ubr] = cOri[drb];
		cOri[drb] = cOri[dfr];
		cOri[dfr] = cOri[urf];
		cOri[urf] = tOri;

		change(Cubos[eOri[ur]]->idCenter, Cubos[eOri[fr]]->idCenter, Cubos[eOri[dr]]->idCenter, Cubos[eOri[ur]]->idCenter);
		tOri = eOri[ur];
		eOri[ur] = eOri[br];
		eOri[br] = eOri[dr];
		eOri[dr] = eOri[fr];
		eOri[fr] = tOri;
	}
}

void cuboRubik::Left(bool p) {
	if (!p) {
		Cubos[12]->rotar(Rx); // BLUE
		for (int i = 0; i < camadasC[5].size(); i++) {
			//cout << "camadas: " << camadasC[5][i] << "  " << i << ": " << cOri[camadasC[5][i]] << " , ";
			Cubos[cOri[camadasC[5][i]]]->rotar(Rx);
		}
		for (int i = 0; i < camadasE[5].size(); i++) {
			Cubos[eOri[camadasE[5][i]]]->rotar(Rx);
		}
	}
	else {
		change(Cubos[cOri[dlf]]->idCenter, Cubos[cOri[dbl]]->idCenter, Cubos[cOri[ulb]]->idCenter, Cubos[cOri[ufl]]->idCenter);
		int tOri = cOri[dlf];
		cOri[dlf] = cOri[ufl];
		cOri[ufl] = cOri[ulb];
		cOri[ulb] = cOri[dbl];
		cOri[dbl] = tOri;

		change(Cubos[eOri[bl]]->idCenter, Cubos[eOri[ul]]->idCenter, Cubos[eOri[fl]]->idCenter, Cubos[eOri[dl]]->idCenter);
		tOri = eOri[bl];
		eOri[bl] = eOri[dl];
		eOri[dl] = eOri[fl];
		eOri[fl] = eOri[ul];
		eOri[ul] = tOri;
	}
}

void cuboRubik::Left2(bool p) {
	if (!p) {
		Cubos[12]->rotar(Rx2); // BLUE
		for (int i = 0; i < camadasC[5].size(); i++) {
			Cubos[cOri[camadasC[5][i]]]->rotar(Rx2);
		}
		for (int i = 0; i < camadasE[5].size(); i++) {
			Cubos[eOri[camadasE[5][i]]]->rotar(Rx2);
		}
	}
	else {
		change(Cubos[cOri[dbl]]->idCenter, Cubos[cOri[dlf]]->idCenter, Cubos[cOri[ufl]]->idCenter, Cubos[cOri[ulb]]->idCenter);
		int tOri = cOri[dbl];
		cOri[dbl] = cOri[ulb];
		cOri[ulb] = cOri[ufl];
		cOri[ufl] = cOri[dlf];
		cOri[dlf] = tOri;

		change(Cubos[eOri[ul]]->idCenter, Cubos[eOri[bl]]->idCenter, Cubos[eOri[dl]]->idCenter, Cubos[eOri[fl]]->idCenter);
		tOri = eOri[ul];
		eOri[ul] = eOri[fl];
		eOri[fl] = eOri[dl];
		eOri[dl] = eOri[bl];
		eOri[bl] = tOri;
	}
}


void cuboRubik::Front(bool p) {
	if (!p) {
		Cubos[4]->rotar(Rz2); // RED
		for (int i = 0; i < camadasC[0].size(); i++) {
			Cubos[cOri[camadasC[0][i]]]->rotar(Rz2);
		}
		for (int i = 0; i < camadasE[0].size(); i++) {
			Cubos[eOri[camadasE[0][i]]]->rotar(Rz2);
		}
	}
	else {
		change(Cubos[cOri[urf]]->idCenter, Cubos[cOri[dfr]]->idCenter, Cubos[cOri[dlf]]->idCenter, Cubos[cOri[ufl]]->idCenter);
		int tOri = cOri[urf];
		cOri[urf] = cOri[ufl];
		cOri[ufl] = cOri[dlf];
		cOri[dlf] = cOri[dfr];
		cOri[dfr] = tOri;

		change(Cubos[eOri[uf]]->idCenter, Cubos[eOri[fr]]->idCenter, Cubos[eOri[df]]->idCenter, Cubos[eOri[fl]]->idCenter);
		tOri = eOri[uf];
		eOri[uf] = eOri[fl];
		eOri[fl] = eOri[df];
		eOri[df] = eOri[fr];
		eOri[fr] = tOri;
	}
}

void cuboRubik::Front2(bool p) {
	if (!p) {
		Cubos[4]->rotar(Rz); // RED
		for (int i = 0; i < camadasC[0].size(); i++) {
			Cubos[cOri[camadasC[0][i]]]->rotar(Rz);
		}
		for (int i = 0; i < camadasE[0].size(); i++) {
			Cubos[eOri[camadasE[0][i]]]->rotar(Rz);
		}
	}
	else {
		change(Cubos[cOri[dfr]]->idCenter, Cubos[cOri[urf]]->idCenter, Cubos[cOri[ufl]]->idCenter, Cubos[cOri[dlf]]->idCenter);
		int tOri = cOri[dfr];
		cOri[dfr] = cOri[dlf];
		cOri[dlf] = cOri[ufl];
		cOri[ufl] = cOri[urf];
		cOri[urf] = tOri;

		change(Cubos[eOri[fr]]->idCenter, Cubos[eOri[uf]]->idCenter, Cubos[eOri[fl]]->idCenter, Cubos[eOri[df]]->idCenter);
		tOri = eOri[fr];
		eOri[fr] = eOri[df];
		eOri[df] = eOri[fl];
		eOri[fl] = eOri[uf];
		eOri[uf] = tOri;
	}
}

void cuboRubik::Back(bool p) {
	if (!p) {
		Cubos[21]->rotar(Rz); // ORA
		for (int i = 0; i < camadasC[1].size(); i++) {
			Cubos[cOri[camadasC[1][i]]]->rotar(Rz);
		}
		for (int i = 0; i < camadasE[1].size(); i++) {
			Cubos[eOri[camadasE[1][i]]]->rotar(Rz);
		}
	}
	else {
		change(Cubos[cOri[ulb]]->idCenter, Cubos[cOri[dbl]]->idCenter, Cubos[cOri[drb]]->idCenter, Cubos[cOri[ubr]]->idCenter);
		int tOri = cOri[ulb];
		cOri[ulb] = cOri[ubr];
		cOri[ubr] = cOri[drb];
		cOri[drb] = cOri[dbl];
		cOri[dbl] = tOri;

		change(Cubos[eOri[br]]->idCenter, Cubos[eOri[ub]]->idCenter, Cubos[eOri[bl]]->idCenter, Cubos[eOri[db]]->idCenter);
		tOri = eOri[br];
		eOri[br] = eOri[db];
		eOri[db] = eOri[bl];
		eOri[bl] = eOri[ub];
		eOri[ub] = tOri;
	}

}

void cuboRubik::Back2(bool p) {
	if (!p) {
		Cubos[21]->rotar(Rz2); // ORA
		for (int i = 0; i < camadasC[1].size(); i++) {
			Cubos[cOri[camadasC[1][i]]]->rotar(Rz2);
		}
		for (int i = 0; i < camadasE[1].size(); i++) {
			Cubos[eOri[camadasE[1][i]]]->rotar(Rz2);
		}
	}
	else {
		change(Cubos[cOri[dbl]]->idCenter, Cubos[cOri[ulb]]->idCenter, Cubos[cOri[ubr]]->idCenter, Cubos[cOri[drb]]->idCenter);
		int tOri = cOri[dbl];
		cOri[dbl] = cOri[drb];
		cOri[drb] = cOri[ubr];
		cOri[ubr] = cOri[ulb];
		cOri[ulb] = tOri;

		change(Cubos[eOri[ub]]->idCenter, Cubos[eOri[br]]->idCenter, Cubos[eOri[db]]->idCenter, Cubos[eOri[bl]]->idCenter);
		tOri = eOri[ub];
		eOri[ub] = eOri[bl];
		eOri[bl] = eOri[db];
		eOri[db] = eOri[br];
		eOri[br] = tOri;
	}
}