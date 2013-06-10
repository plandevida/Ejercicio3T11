#include <iostream>

using namespace std;

const int N = 8;

void calcularXY( int &x, int &y , int v);
bool esValido(int tablero[][N], int &x, int &y);
bool buscaCasilla(int tablero[N][N], int valor, int &x, int &y);
void buscaUltimaCasilla(int tablero[N][N], int &x, int &y, int &k);
void imprimeTablero(int tablero[N][N]);
bool esSolucion(int k);
void caballo(int tablero[N][N], int k, int x, int y, bool &encontrado);
void caballo2(int tablero[N][N], int k, int x, int y, bool &encontrado);

/*
 * Recibe un tablero relleno con los primeros k saltos del caballo y termina
 * de rellenarlo. El caballo se encuentra inicialmente en el posición (x,y).
 * Al finalizar "encontrado" indica si se ha encontrado una solución al problema.
 */
void caballo(int tablero[N][N], int k, int x, int y, bool &encontrado) {
	
    int xaux;
    int yaux;
    
    for(int i=0; i<8 && !encontrado;i++) {
		xaux = x;
        yaux = y;
        
        calcularXY( xaux, yaux, i);
        
        if (esValido(tablero,xaux,yaux)) {
            tablero[xaux][yaux] = k;
            
            if(esSolucion(k)) {
                encontrado=true;
            }
            else {
                caballo(tablero, k+1, xaux, yaux, encontrado);
                
                if ( !encontrado ) {
                    tablero[xaux][yaux] = 0;
                }
            }
        }
    }
}

bool esValido(int tablero[N][N], int &x, int &y) {
	return (( x >= 0 && x < N ) && ( y >= 0 && y < N ) && ( tablero[x][y] == 0 ));
}

bool esSolucion(int k) {
    
	return (N*N==k);
}

void calcularXY( int &x, int &y , int v) {
	switch(v) {
        case 0:
            x+=1;
            y-=2;
            break;
		case 1:
            x+=2;
            y-=1;
            break;
		case 2:
            x+=2;
            y+=1;
            break;
		case 3:
            x+=1;
            y+=2;
            break;
		case 4:
            x-=1;
            y+=2;
            break;
		case 5:
            x-=2;
            y+=1;
            break;
		case 6: 
            x-=2;
            y-=1;
            break;
		case 7: 
            x-=1;
            y-=2;
            break;
    }
}


/*
 * Busca una casilla en el tablero que contenga un cierto valor. En caso de 
 * encontrarla devuelve true y en (x,y) las coordenadas de dicha casilla.
 */
bool buscaCasilla(int tablero[N][N], int valor, int &x, int &y) {
	for (int i = 0; i < N; i++) {
		for (int j=0; j<N; j++) {
			if (tablero[i][j] == valor) {
				x = i;
				y = j;
				return true;
			}
		}
	}
	
	return false;
}

/*
 * Dado un tablero incompleto devuelve el número del último salto en k
 * y su posición en (x,y).
 * Asumimos que todos los saltos en el tablero son consecutivos y correctos.
 */
void buscaUltimaCasilla(int tablero[N][N], int &x, int &y, int &k) {
	for (int i=1; i<=N*N; i++) {
		if (!buscaCasilla(tablero, i, x, y)) {
			k = i;
			return;
		}
	}
}

/*
 * Imprime un tablero por la consola.
 */
void imprimeTablero(int tablero[N][N]) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cout << tablero[i][j] << "\t";
		}
		cout << endl;
	}
}

/*
 * Rellena un tablero incompleto y lo imprime por la consola.
 */
void resuelve(int tablero[N][N]) {
	int x, y, k;
	buscaUltimaCasilla(tablero, x, y, k);
	
	bool encontrado = false;
	
	//imprimeTablero(tablero);
	//cout << endl;
	
	caballo(tablero, k, x, y, encontrado);
	
	if (encontrado) {
		imprimeTablero(tablero);
	} else {
		cout << "Sin solución" << endl;
	}
	cout << endl;
}

/*
 * Tratamos de rellenar distintos tableros incompletos.
 */
int main() {
	int tablero1[N][N] = {
		{63, 14, 37, 24, 51, 26, 35, 10},
		{22, 39, 62, 13, 36, 11, 50, 27},
		{15, 0, 23, 38, 25, 52,  9, 34},
		{40, 21, 16, 61, 12, 33, 28, 49},
		{17, 60,  1, 44, 29, 48, 53,  8},
		{ 2, 41, 20, 57,  6, 55, 32, 47},
		{59, 18, 43,  4, 45, 30,  7, 54},
		{42,  3, 58, 19, 56,  5, 46, 31}
	};
	
	int tablero2[N][N] = {
		{0, 14, 37, 24, 0, 26, 35, 10},
		{22, 39, 0, 13, 36, 11, 0, 27},
		{15, 0, 23, 38, 25, 0,  9, 34},
		{40, 21, 16, 0, 12, 33, 28, 49},
		{17, 0,  1, 44, 29, 48, 0,  8},
		{ 2, 41, 20, 0,  6, 0, 32, 47},
		{0, 18, 43,  4, 45, 30,  7, 0},
		{42,  3, 0, 19, 0,  5, 46, 31}
	};
	
	int tablero3[N][N] = {
		{0, 14, 37, 24, 0, 26, 35, 10},
		{22, 39, 0, 13, 36, 11, 0, 27},
		{15, 0, 23, 38, 25, 0,  9, 34},
		{40, 21, 16, 0, 12, 33, 28, 0},
		{17, 0,  1, 0, 29, 0, 0,  8},
		{ 2, 0, 20, 0,  6, 0, 32, 0},
		{0, 18, 0,  4, 0, 30,  7, 0},
		{0,  3, 0, 19, 0,  5, 0, 31}
	};
	
	int tablero4[N][N] = {
		{0, 14, 0, 24, 0, 26, 0, 10},
		{22, 0, 0, 13, 0, 11, 0, 27},
		{15, 0, 23, 0, 25, 0,  9, 0},
		{0, 21, 16, 0, 12, 0, 28, 0},
		{17, 0,  1, 0, 29, 0, 0,  8},
		{ 2, 0, 20, 0,  6, 0, 0, 0},
		{0, 18, 0,  4, 0, 30,  7, 0},
		{0,  3, 0, 19, 0,  5, 0, 0}
	};
	
	int tablero5[N][N] = {
		{0, 14, 0, 0, 0, 0, 0, 10},
		{0, 0, 0, 13, 0, 11, 0, 0},
		{15, 0, 0, 0, 0, 0,  9, 0},
		{0, 0, 16, 0, 12, 0, 0, 0},
		{17, 0,  1, 0, 0, 0, 0,  8},
		{ 2, 0, 0, 0,  6, 0, 0, 0},
		{0, 18, 0,  4, 0, 0,  7, 0},
		{0,  3, 0, 19, 0,  5, 0, 0}
	};
	
	cout << "tablero 1" << endl;
	resuelve(tablero1);
	
	cout << "tablero 2" << endl;
	resuelve(tablero2);

	cout << "tablero 3" << endl;
	resuelve(tablero3);	

	cout << "tablero 4" << endl;
	resuelve(tablero4);

	cout << "tablero 5" << endl;
	resuelve(tablero5);
	
	return 0;
}
