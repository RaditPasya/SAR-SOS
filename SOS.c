#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

int n,player,comp;
char arr[25][25];
bool papanPenuh=false;
//daftar modul

void player_move();
void comp_move();
int cari_os();
int cari_ss();
int find_square();
bool square_valid(int row, int col);
void besarPapan();
void inis_papan();
void Gambar_Papan(int n);
void pilihKotak();
int kotaky(char y);
int cek_sos(int row, int col,int o,char symbol);
int cek_papan();

/* MAIN PROGRAM */

int main(){	
	int play;

	printf("Halo! Selamat datang di game SOS!\n");
	printf("Ketik 1 untuk main atau ketik 0 untuk keluar dari permainan = ");
	scanf("%d", &play);
	if(play==1){
		while(play==1){
			printf("\nNah, sebelum main, tentukan dulu besar papannya!\n");
			printf("Kamu bisa main di papan sebesar 3x3 sampai 25x25.\n");
			printf("Sekarang, tolong ketik satu bilangan integer mulai dari 3 sampai 25!\n");
			besarPapan();
			inis_papan();
			Gambar_Papan(n);
			do
			{
				player_move();
				comp_move();				
			} while (cek_papan());
			
			printf("****************************************************************\nPermainan selesai dengan score player = %d dan computer = %d\n****************************************************************\n", player,comp);
			if (player>comp)
			{
				printf("Selamat anda menang!\n");
			}
			else
			{
				printf("Sayang sekali anda kalah\n");
			}
			
			
			printf("****************************************************************\nKetik 1 untuk main lagi atau ketik 0 untuk keluar dari permainan = ");
			scanf("%d", &play);
		}
	}
	if(play==0){
		
		printf("\nDadah!");
	}
	
	return 0;
}


//modul-modul

void player_move(){
	pilihKotak();
	Gambar_Papan(n);

	return;
}

void comp_move(){
  int square;
  int row, col;
  int random;
  char huruf;
  printf("\nGiliran computer di mulai!\n");

  do
  {
    Gambar_Papan(n);
	if(cari_os())
	{
		square = cari_os();
		huruf = 'S';
	}
	else if(cari_ss())
	{
		square = cari_ss();
		huruf = 'O';
	}
	else
	{
		square = find_square();
		random = (rand() % (10 - 1)+1);
		if (random%2==0)
		{
			huruf = 'S';
		}
		else
		{
			huruf = 'O';
		}
		
		
	}
	row = (square-1)/n;
	col = (square-1)%n;
        
   	arr[row][col] = huruf;
   }while(cek_sos(row,col,2,huruf));

   Gambar_Papan(n);
   printf("\nGiliran computer telah selesai!\n");
   return;
}

int cari_os ()
{
	int square;

	for (int ii=0; ii<n; ii++)
	{
		for(int jj=0; jj<n; jj++)
		{
		   square = ((ii*n) +jj)+1;
		   if(arr[ii][jj]==' ')
		   {
			if((arr[ii][jj+1]=='O') && (arr[ii][jj+2] == 'S'))
			{
				return square;
			}
                       if((arr[ii][jj-1]=='O') && (arr[ii][jj-2] == 'S'))
                        {
                                return square;
                        }
			if ((arr[ii+1][jj] == 'O') && (arr[ii+2][jj] =='S'))
			{
				return square;
			}
                        if ((arr[ii-1][jj] == 'O') && (arr[ii-2][jj] =='S'))
                        {
                                return square;
                        }
			if((arr[ii+1][jj+1] == 'O') && (arr[ii+2][jj+2] == 'S'))
                        {
                                return square;
                        }
                        if((arr[ii-1][jj-1] == 'O') && (arr[ii-2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((arr[ii+1][jj-1] == 'O') && (arr[ii+2][jj-2] == 'S'))
                        {
                                return square;
                        }
                        if((arr[ii-1][jj+1] == 'O') && (arr[ii-2][jj+2] == 'S'))
                        {
                                return square;
                        }
		  }
		}
	}
	return 0;
}

int cari_ss()
{
	int square;

        for (int ii=0; ii<n; ii++)
        {
                for(int jj=0; jj<n; jj++)
                {  
                   square = ((ii*n) +jj)+1;

                   if(arr[ii][jj]==' ')
                   {

		        if((arr[ii][jj+1]=='S') && (arr[ii][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if ((arr[ii+1][jj] == 'S') && (arr[ii-1][jj] =='S'))
                        {
                                return square;
                        }
                        if((arr[ii+1][jj+1] == 'S') && (arr[ii-1][jj-1] == 'S'))
                        {
                                return square;
                        }
                        if((arr[ii+1][jj-1] == 'S') && (arr[ii-1][jj+1] == 'S'))
                        {
                                return square;
                        }
                  }
		}
        }
	return 0;
}

int find_square()
{
	int row, col, square;
	
	for (square=1; square<((n*n)+1); square++)
	{
		row = (square-1)/n;
		col = (square-1)%n;
		if (arr[row][col] == ' ')
		{
			return square;
		}
	}
	return 0;
}

void besarPapan(){
	bool benar=false;

	while(benar==false){
		printf("\nTolong ketik satu bilangan integer mulai dari 3 sampai 25!\n");
		printf("Pilihanmu = ");
		scanf("%d", &n);
		if(n<3){
			printf("Papan tidak lebih kecil dari 3x3!\n");
		}
		else{
			if(n>25){
				printf("Papan tidak lebih besar dari 25x25!\n");
			}
			else if (n!=3 || n!=4 || n!=4 || n!=3 || n!=3 || n!=3 || n!=3){
				benar=true;
			}
		}	
	}
	printf("****************************************************************");
	printf("\nKamu akan bermain di kotak sebesar %dx%d.", n, n);
	printf("\n\n");
	printf("Selamat bermain!\n");
	printf("\n");

	return;
}

void inis_papan(){
	for (int row = 0; row < n; row++)
	{
		for (int col=0; col<n; col++)
		{
			arr[row][col]=' ';
		}
	}
	player = 0;
	comp = 0;
	return;
}

void Gambar_Papan(int n){
	printf("\n");
	int row, col, counter=3, counter2=1;
	char tanda = 65;
	printf("  ");
			for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				if (ii==counter)
				{
					printf("%c", tanda); //menggambarkan huruf2 penanda diatas papan
					tanda++;
					counter = counter + 4;
				}
				else
				{
					printf(" ");
				}
				
			}
	printf("\n   ");
	for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
	for ( row=0; row<n; row++)
	{
		printf(" %d |", counter2); // Menggambarkan angka disamping baris
		counter2++; 
		for (col=0; col<n; col++)
		{
			printf(" %c |",arr[row][col]);
		}
		printf(" \n");
		if (row != n)
		{
			printf("   ");
			for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
		}
	}
	printf("\n");		
	return;
}

void pilihKotak(){
	int x,row,col;
	char y,huruf;
	do
	{
		do
		{
			fflush(stdin);
			printf("\nPilih kotak yang akan diisi = ");
			scanf("%d%c", &x, &y);
			row = x-1;
			col=kotaky(y);
		} while (arr[row][col]!=' ');

			printf("Pilih huruf S atau O = ");
			scanf(" %c", &huruf);
			printf("Giliran player berakhir!\n\n");
			printf("\n");
		
		
		
		arr[row][col]=toupper(huruf);
	} while (cek_sos(row,col,1,toupper(huruf)));
	
	
	return;
	
}

bool square_valid (int row, int col)
{
	printf("\nNilai array 7%c7", arr[row][col]);
   
	if (arr[row][col]==' ')
	{
		printf("\nKotak Valid\n");
		return true;
	}
	else 
	{
		printf("\nKotak Tidak Valid\n");
		return false;
	} 
}

int kotaky(char y){
	int kolom;
	switch(y){
		case 'A' : kolom=0;break;
		case 'a' : kolom=0;break;
		case 'B' : kolom=1;break;
		case 'b' : kolom=1;break;
		case 'C' : kolom=2;break;
		case 'c' : kolom=2;break;
		case 'D' : kolom=3;break;
		case 'd' : kolom=3;break;
		case 'E' : kolom=4;break;
		case 'e' : kolom=4;break;
		case 'F' : kolom=5;break;
		case 'f' : kolom=5;break;
		case 'G' : kolom=6;break;
		case 'g' : kolom=6;break;
		case 'H' : kolom=7;break;
		case 'h' : kolom=7;break;
		case 'I' : kolom=8;break;
		case 'i' : kolom=8;break;
		case 'J' : kolom=9;break;
		case 'j' : kolom=9;break;
		case 'K' : kolom=10;break;
		case 'k' : kolom=10;break;
		case 'L' : kolom=11;break;
		case 'l' : kolom=11;break;
		case 'M' : kolom=12;break;
		case 'm' : kolom=12;break;
		case 'N' : kolom=13;break;
		case 'n' : kolom=13;break;
		case 'O' : kolom=14;break;
		case 'o' : kolom=14;break;
		case 'P' : kolom=15;break;
		case 'p' : kolom=15;break;
		case 'Q' : kolom=16;break;
		case 'q' : kolom=16;break;
		case 'R' : kolom=17;break;
		case 'r' : kolom=17;break;
		case 'S' : kolom=18;break;
		case 's' : kolom=18;break;
		case 'T' : kolom=19;break;
		case 't' : kolom=19;break;
		case 'U' : kolom=20;break;
		case 'u' : kolom=20;break;
		case 'V' : kolom=21;break;
		case 'v' : kolom=21;break;
		case 'W' : kolom=22;break;
		case 'w' : kolom=22;break;
		case 'X' : kolom=23;break;
		case 'x' : kolom=23;break;
		case 'Y' : kolom=24;break;
		case 'y' : kolom=24;break;
 	}
	return kolom;
}

int cek_sos(int row, int col,int o,char symbol){
	int sos = 0;
	
  if(symbol == 'S')
  {
	if ((arr[row][col-2] == 'S') && (arr[row][col-1] == 'O'))
	{
		sos++;
	}
	if ((arr[row][col+1]== 'O') && (arr[row][col+2] == 'S'))
	{
		sos++;
	}	
	if((arr[row+1][col] == 'O') && (arr[row+2][col] == 'S'))
	{
		sos++;
	}
	if((arr[row-1][col] == 'O') && (arr[row-2][col] == 'S'))
	{
		sos++;
	}
	if((arr[row+1][col+1] == 'O') && (arr[row+2][col+2] == 'S'))
	{
		sos++;
	}
	if((arr[row-1][col-1] == 'O') && (arr[row-2][col-2] == 'S'))
	{
		sos++;
	}
	if((arr[row+1][col-1] == 'O') && (arr[row+2][col-2] == 'S'))
	{
		sos++;
	}
	if((arr[row-1][col+1] == 'O') && (arr[row-2][col+2] == 'S'))
	{
		sos++;
	}
  }
  else if(symbol == 'O')
  {
	if((arr[row+1][col] == 'S') && (arr[row-1][col] == 'S'))
	{
		sos++;
	}
	if((arr[row][col+1] == 'S') && (arr[row][col-1] == 'S'))
	{
		sos++;
	}
	if((arr[row+1][col+1] == 'S') && (arr[row-1][col-1] == 'S'))
	{
		sos++;
	}
	if((arr[row+1][col-1] == 'S') && (arr[row-1][col+1] == 'S'))
	{
		sos++;
	}
  }


	if (o == 1 && sos>0)
	{
		player= player + sos;
		Gambar_Papan(n);
		printf("\nPlayer mendapatkan %d poin!\nGiliran Player lagi!", sos);
	}
	else if (o == 2 && sos>0)
	{
		comp= comp + sos;
		Gambar_Papan(n);
		printf("\nComp mendapatkan %d poin!\n", sos);	
	}
	


	if (sos>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int cek_papan(){

	int row, col;
	
	for (row=0; row<n; row++)
	{
		for(col=0; col<n; col++)
		{
			if (arr[row][col] == ' ')
			{
				return 1;
			}
		}
	}
	
	return 0;
}