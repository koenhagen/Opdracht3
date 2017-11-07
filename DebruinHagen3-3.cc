#include <iostream>
#include <climits>
#include <fstream>
#include <unistd.h>

using namespace std;

const int MAX = 100;

void leesoptie ( char& keuze ) {
	char prevkeuze = '\n';
   while ( prevkeuze == '\n' ) {
      prevkeuze = keuze;
      cin.get ( keuze );
   }
   if ( keuze != '\n' ) {
      keuze = '\0';
   } else {
      keuze = prevkeuze;
   }
   cin.ignore (INT_MAX, '\n');
}

void leesgetal ( char& keuze ) {
 	char prevkeuze = '\n';
 	int getal = 0;
   while ( prevkeuze == '\n' || keuze != '\n') {
      prevkeuze = keuze;
      cin.get ( keuze );
      if ( keuze >= '0' && keuze <= '9' && getal < 1000 ) {
         getal = ( getal * 10 ) + ( keuze - '0' );
      }
   }
}

int randomgetal ( ) {
   static long getal = 42;
   getal = ( 221 * getal + 1 ) % 1000;
   return getal;
}  // randomgetal

class life {
   public:
      life ();
      void drukaf ( );
      void vulrandom ( );
      void maakschoon ( );
      void maakviewschoon ( );
      void gaan ( );
      void glidergun ( );
      void verschuiflinks ( );
      void verschuifrechts ( );
      void verschuifboven ( );
      void verschuifonder ( );
   private:
      bool wereld[MAX][MAX];
      bool hulpwereld[MAX][MAX];
      int startcolumn, startrow, viewwidth, viewlength, verschuifstapgrootte, schoonvariabele;
      int schuif, percentage, generaties;
}; // life

life::life ( ) {
   startcolumn = 0;
   startrow = 0;
   viewwidth = 40;
   viewlength = 20;
   verschuifstapgrootte = 90;
   percentage = 21;

} // life::life

void life::drukaf ( ) {
	for (int i = 0; i < MAX; i++ ) {
		for (int j = 0; j < MAX; j++ ) {
			if ( i >= startrow && i < startrow + viewlength && j >= startcolumn
			     && j < startcolumn + viewwidth ) {
				if ( i == 0 || j == 0 || i == MAX - 1|| j == MAX - 1) {
				   cout << "# ";
				}
				else if ( wereld[i][j] == false ) {
					cout << ". ";
				}
				else {
				    cout << "x ";
				}
			}
		}
		if ( i >= startrow && i < startrow + viewlength ) {
	cout << endl;
		}
	}
} // life::drukaf

void life::maakviewschoon ( ) {
   for (int i = startcolumn; i < startcolumn + viewlength; i++ ) {
      for (int j = startrow; j < startrow + viewwidth; j++ ) {
         wereld[i][j] = false;
      }
   }
} // life::maakschoon

void life::maakschoon ( ) {
   for (int i = 0; i < MAX; i++ ) {
      for (int j = 0; j < MAX; j++ ) {
         wereld[i][j] = false;
      }
   }
} // life::maakschoon

void life::glidergun ( ) {
	ifstream invoer ("glidergun.txt",ios::in );
	char kar;
		for ( int i = 0; i < MAX; i++ ) {
			for ( int j = 0; j < MAX; j++ ) {
				kar = invoer.get();
				if ( kar == '\n' ) {
					break;
				}
				else if ( kar == 'x' ) {
					wereld[i][j] = true;
				}
			}
		}
}

void life::vulrandom ( ) {
   int r;
   for (int i = 0; i < MAX; i++ ) {
      for (int j = 0; j < MAX; j++ ) {
         r = randomgetal ( );
         if ( r < percentage*10 ) {
         wereld[i][j] = true;
         }
         else {
         wereld[i][j] = false;
         }
      }
   }
}

void life::verschuiflinks ( ) {
	if ( startcolumn - verschuifstapgrootte >= 0 && startcolumn != viewwidth) {
	   startcolumn -= verschuifstapgrootte;
   }
   else {
      startcolumn = 0;
   }
}

void life::verschuifrechts ( ) {
   if ( MAX - startcolumn >= verschuifstapgrootte + viewwidth && startcolumn != MAX - viewwidth) {
	   startcolumn += verschuifstapgrootte;
   }
   else {
      startcolumn = MAX - viewwidth;
   }
}

void life::verschuifboven ( ) {
   if ( startrow - verschuifstapgrootte >= 0 && startrow != viewlength ) {
	   startrow -= verschuifstapgrootte;
   }
   else {
      startrow = 0;
   }

}

void life::verschuifonder ( ) {
   if ( MAX - startrow >= verschuifstapgrootte + viewlength && startrow != MAX - viewlength ) {
	   startrow += verschuifstapgrootte;
   }
   else {
      startrow = MAX - viewlength;
   }
}

void life::gaan ( ) {
	int gaanteller = 0;
	for (int i = 0; i < MAX; i++ ) {
		for (int j = 0; j < MAX; j++ ) {
			if ( wereld[i-1][j-1] == true ) {
				gaanteller++;
			}
			if ( wereld[i-1][j] == true ) {
				gaanteller++;
			}
			if ( wereld[i-1][j+1] == true ) {
				gaanteller++;
			}
			if ( wereld[i][j-1] == true ) {
				gaanteller++;
			}
			if ( wereld[i][j+1] == true ) {
		    	gaanteller++;
			}
			if ( wereld[i+1][j-1] == true ) {
		   		gaanteller++;
			}
			if ( wereld[i+1][j] == true ) {
		   		gaanteller++;
			}
			if ( wereld[i+1][j+1] == true ) {
				gaanteller++;
			}
			if ( (wereld[i][j] == true && ( gaanteller < 2 || gaanteller > 3 ) ) || ( wereld[i][j] == false && gaanteller != 3 ) ) {
			hulpwereld[i][j] = false;
			}
			else {
			hulpwereld[i][j] = true;
			}
			gaanteller = 0;
		}
	}
	for (int i = 0; i < MAX; i++ ) {
		for (int j = 0; j < MAX; j++ ) {
			wereld[i][j] = hulpwereld[i][j];
		}
	}
}

void submenuverschuif( life& Box1) {
	char verschuifkeuze = '\n';
	bool stopsubmenu = false;
	while ( stopsubmenu != true ) {
		cout << "Hoe wilt u verschuiven?"
	        << " Gebruik WASD & s(T)oppen" << endl;

      leesoptie( verschuifkeuze );

		switch ( verschuifkeuze ) {
			case 'A':
         case 'a': {
				Box1.verschuiflinks ( );
				Box1.drukaf ( );
				}
			break;
			case 'S':
         case 's': {
				Box1.verschuifonder ( );
				Box1.drukaf ( );
				}
			break;
			case 'D':
         case 'd': {
				Box1.verschuifrechts ( );
				Box1.drukaf ( );
				}
			break;
			case 'W':
         case 'w': {
				Box1.verschuifboven ( );
				Box1.drukaf ( );
				}
			break;
			case 'T':
         case 't': {
				stopsubmenu = true;
				}
			break;
			default:
				cout << "Not a Valid subkeuze. \n";
				cout << "Choose again.\n";
			break;
		}
		verschuifkeuze = '\n';
	}
}

void submenu( ) {
	char subkeuze = '\n';
	bool stopsubmenu = false;
	while ( stopsubmenu != true ) {
		//cout << " **********************************************" << endl;
		cout << " - (V)erschuifings-stapgrootte";
		cout << " - (P)ercentage";
		cout << " - (T)ekens dood/levend" << endl;
		cout << " Wat wilt u doen? ";

      leesoptie( subkeuze );

		switch ( subkeuze ) {
			case 'C':
				cout << "game start!\n";
				// rest of code here
			break;
			case 'R':
				cout << "Story so far....\n";
				// rest of code here
			break;
			case 'P':
				submenu( );
			break;
			case 'S':
				cout << "End of Program.\n";
				stopsubmenu = true;
			break;
			default:
				cout << "Not a Valid subkeuze. \n";
				cout << "Choose again.\n";
			break;
		}
		subkeuze = '\n';
	}
}

int main( ) {
   char keuze = '\n';
	bool stopmenu = false;
	life Box1;
	while ( stopmenu != true ) {
	//	cout << " **********************************************" << endl;
		cout << " (S)toppen";
		cout << " - (H)eelschoon";
		cout << " - s(C)hoon";
		cout << " - (V)erschuiven";
		cout << " - (P)arameters" << endl;
		cout << " - (R)andom";
		cout << " - (T)oggle";
		cout << " - g(L)idergun";
		cout << " - (E)en";
		cout << " - (G)aan" << endl;
		cout << "Wat wilt u doen: ";

      leesoptie( keuze );

		switch ( keuze ) {
		   case 'S':
         case 's':
				cout << "End of Program.\n";
				stopmenu = true;
			break;
			case 'H':
         case 'h': {
				Box1.maakschoon ( );
				Box1.drukaf ( );
				}
			break;
			case 'C':
         case 'c': {
				Box1.maakviewschoon ( );
				Box1.drukaf ( );
				}
			break;
			case 'V':
			case 'v':
			   submenuverschuif ( Box1 );
			break;
			case 'R':
         case 'r': {

				Box1.vulrandom ( );
				Box1.drukaf ( );
			}
			break;
			case 'P':
         case 'p':
				submenu( );
			break;
			case 'L':
         case 'l': {
				Box1.glidergun ( );
				Box1.drukaf ( );
			}
			break;
			case 'E':
         case 'e': {
				Box1.gaan ( );
				Box1.drukaf ( );
			}
			break;
			case 'G':
         case 'g': {
				for ( int j = 0; j < 10000; j++ ) {
					Box1.gaan ( );
					Box1.drukaf ( );
					usleep(50000);
				}
			}
			break;
			default:
				cout << "Not a Valid keuze. \n";
				cout << "Choose again.\n";
			break;
		}
		keuze = '\n';
	}
	return 0;
}
