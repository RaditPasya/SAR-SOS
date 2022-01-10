#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int n,player1,comp,player2, HighScore;
int mode_main,kesulitan;
char arr[15][15];
char nama1[30],nama2[30],Pemenang[35];
bool papanPenuh=false;
FILE * fpointer;
//daftar modul

void menu_utama();
void peraturan();
void player_move(int r);
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
void end_game(int k);

/* MAIN PROGRAM */

int main(){	
	int play=0;

	while (play==0){
		system("cls");
		menu_utama();
		scanf("%d", &play);
		
		if(play==1){
			system("cls");
			while(play==1){
				do
			    {
	    			fflush(stdin);
    				printf("*  . \n\n");
					printf("  Tentukan mode permainan\n  1) Player vs Comp\n  2) Player vs Player\n  3) Player vs Player vs Comp\n\n   > Pilihanmu = ");
					scanf("%d", &mode_main);
    			} while (mode_main!=1 && mode_main!=2 && mode_main!=3);
    			if (mode_main==1||mode_main==3)
    			{
        			do
        			{
        			    fflush(stdin);
        			    printf("\n. . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
        			    printf("\n  Karena kamu memilih mode yang melibatkan computer\n  maka pilih tingkat kesulitan computer dari 1 (mudah) sampai 3 (sulit)\n\n   > Pilihanmu = ");
            			scanf("%d", &kesulitan);
        			} while (kesulitan!=1 && kesulitan!=2 && kesulitan!=3);
        
        
    			}
    			printf("\n. . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
				printf("\n  Nah, sebelum main, tentukan dulu besar papannya!\n");
				printf("  Kamu bisa main di papan sebesar 3x3 sampai 15x15.\n");
				besarPapan();
				inis_papan();
				Gambar_Papan(n);
				if (mode_main==1)
				{
					printf("Sekarang, tolong masukkan nama dari player 1 (tanpa spasi): ");
            	    scanf("%s",nama1);
					do
					{
						player_move(1);
                	    if (!cek_papan())
                    	{
                    	    break;
                    	}
                    
						comp_move();			
					} while (cek_papan());
				}
				else if (mode_main==2)
				{
    	            printf("Sekarang, tolong masukkan nama dari player 1 (tanpa spasi): ");
    	            scanf("%s",nama1);
    	            fflush(stdin);
    	            printf("\nSelanjutnya, tolong masukkan nama dari player 2 (tanpa spasi): ");
    	            scanf("%s",nama2);
					do
					{
						player_move(1);
        	            if (!cek_papan())
            	        {
    	                    break;
        	            }
						player_move(2);				
					} while (cek_papan());
				}
        	    else if (mode_main==3)
        	    {
        	        printf("Sekarang, tolong masukkan nama dari player 1 (tanpa spasi): ");
        	        scanf("%s",nama1);
        	        fflush(stdin);
            	    printf("\nSelanjutnya, tolong masukkan nama dari player 2 (tanpa spasi): ");
            	    scanf("%s",nama2);
					do
					{
						player_move(1);
            	        if (!cek_papan())
            	        {
            	            break;
            	        }
						player_move(2);
            	        if (!cek_papan())
            	        {
            	            break;
            	        }
            	        comp_move();				
					} while (cek_papan());
				}
            
				end_game(mode_main);
				printf("****************************************************************\nKetik 1 untuk main lagi atau ketik 0 untuk kembali ke menu utama = ");
				scanf("%d", &play);
				system("cls");
			}
		}
		
		if (play==2){
			peraturan();
			scanf("%d", &play);
		}
		
		if(play==3){
			system("cls");
		}
	}
	return 0;
}


//modul-modul

void player_move(int r){
	pilihKotak(r);
	Gambar_Papan(n);

	return;
}

void end_game(int k){
    if (k==1)
    {
    	printf("****************************************************************\nPermainan selesai dengan score %s = %d dan Computer = %d\n****************************************************************\n",nama1, player1,comp);
		if (player1==comp)
		{
			printf("%s dan Computer seri!\n", nama1);
		}
		else if (player1>comp)
		{
			printf("Selamat %s menang!\n", nama1);
			if (player1>HighScore){
				fpointer=fopen("pemenang.txt", "w");
				fprintf(fpointer, "%s -", nama1);
				fclose(fpointer);
				fpointer=fopen("highscore.txt", "w");
				fprintf(fpointer, "%d", player1);
				fclose(fpointer);
			}
			
		}
		else
		{
			printf("Sayang sekali anda kalah.\n");
		}
    }
    else if (k==2)
    {
        printf("****************************************************************\nPermainan selesai dengan score %s = %d dan %s = %d\n****************************************************************\n",nama1,player1,nama2,player2);
        if (player1==player2)
        {
        	printf("%s dan %s seri!\n", nama1, nama2);
		}
		else if (player1>player2)
		{
			printf("Selamat %s menang!\n", nama1);
			if (player1>HighScore){
				fpointer=fopen("pemenang.txt", "w");
				fprintf(fpointer, "%s -", nama1);
				fclose(fpointer);
				fpointer=fopen("highscore.txt", "w");
				fprintf(fpointer, "%d", player1);
				fclose(fpointer);
			}
		}
		else
		{
			printf("Selamat %s menang!\n", nama2);
			if (player2>HighScore){
				fpointer=fopen("pemenang.txt", "w");
				fprintf(fpointer, "%s -", nama2);
				fclose(fpointer);
				fpointer=fopen("highscore.txt", "w");
				fprintf(fpointer, "%d", player2);
				fclose(fpointer);
			}
		}
    }
    else if (k==3)
    {
        printf("****************************************************************\nPermainan selesai dengan score %s = %d, %s = %d dan, Computer = %d\n****************************************************************\n",nama1,player1,nama2,player2,comp);
        if (player1==player2 && player1==comp && player2==comp)
        {
        	printf("%s, %s, dan Computer seri!\n", nama1, nama2);
		}
		else if (player1==player2 && player1>comp && player2>comp)
		{
			printf("%s dan %s seri!\n", nama1, nama2);
		}
		else if (player1==comp && player1>player2 && comp>player2)
		{
			printf("%s dan Computer seri!\n", nama1);
		}
		else if (player2==comp && player2>player1 && comp>player1)
		{
			printf("%s dan Computer seri!\n", nama2);
		}
		else if (player1>player2 && player1>comp)
        {
            printf("Selamat %s menang!\n", nama1);
            if (player1>HighScore){
				fpointer=fopen("pemenang.txt", "w");
				fprintf(fpointer, "%s -", nama1);
				fclose(fpointer);
				fpointer=fopen("highscore.txt", "w");
				fprintf(fpointer, "%d", player1);
				fclose(fpointer);
			}
        }
        else if (player2>player1 && player2>comp)
        {
            printf("Selamat %s menang!\n", nama2);
            if (player2>HighScore){
				fpointer=fopen("pemenang.txt", "w");
				fprintf(fpointer, "%s -", nama2);
				fclose(fpointer);
				fpointer=fopen("highscore.txt", "w");
				fprintf(fpointer, "%d", player2);
				fclose(fpointer);
			}
        }
        else
        {
            printf("Kalian kalah sama komputer :(\n");
        }
        
        
    }
    
    
    

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
    if (kesulitan==1)
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
    else if (kesulitan ==2)
    {
	    if(cari_ss())
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
    }
    else if (kesulitan == 3)
    {
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
	
	}
	row = (square-1)/n;
	col = (square-1)%n;
        
   	arr[row][col] = huruf;
   }while(cek_sos(row,col,3,huruf));

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
		printf("\n  Tolong ketik satu bilangan integer mulai dari 3 sampai 15!\n\n");
		printf("   > Pilihanmu = ");
		scanf("%d", &n);
		if(n<3){
			printf("\n. . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
			printf("\n  <!!!> Papan tidak lebih kecil dari 3x3! <!!!>\n");
		}
		else{
			if(n>15){
				printf("\n. . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
				printf("\n  <!!!> Papan tidak lebih besar dari 15x15! <!!!>\n");
			}
			else if (n>=3 || n<=15){
				benar=true;
			}
		}	
	}
}

void inis_papan(){
	for (int row = 0; row < n; row++)
	{
		for (int col=0; col<n; col++)
		{
			arr[row][col]=' ';
		}
	}
	player1 = 0;
    player2 = 0;
	comp = 0;
	return;
}

void Gambar_Papan(int n){
	system("cls");
	printf("\nKamu akan bermain di papan sebesar %dx%d.", n, n);
	printf("\n\n");
	printf("*  . Selamat bermain! .  * \n");
	printf("\n");
	printf("\n");
	int row, col, counter=3, counter2=1;
	char tanda = 65;
	printf("    ");
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
	printf("  ");
	for(int ii=0; ii<((n*4)+1); ii++)
			{ 
				printf("-");
			}
			printf(" \n");
	for ( row=0; row<n; row++)
	{
		if (counter2<10)
		{
			printf(" %d   |", counter2); // Menggambarkan angka disamping baris
		}
		else
		{
			printf(" %d  |", counter2); // Menggambarkan angka disamping baris
		}
		counter2++; 
		for (col=0; col<n; col++)
		{
			printf(" %c |",arr[row][col]);
		}
		printf(" \n");
		if (row != n)
		{
			printf("     ");
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

void pilihKotak(int f){
	int x,row,col;
	char y,huruf;
	bool hurufBenar;
	if (f==1)
	{
        printf("\n****************************************************************");
		printf("\nGiliran %s Dimulai!!\n", nama1);
	}
	else if (f==2)
	{
        printf("\n****************************************************************");
		printf("\nGiliran %s Dimulai!!\n", nama2);
	}
	
	
		
	do
	{
		do
		{
			fflush(stdin);
			printf("\nPilih kotak yang akan diisi = ");
			scanf(" %c%d", &y, &x);
			row = x-1;
			col=kotaky(y);
		} while (arr[row][col]!=' ');
		hurufBenar=false;
		huruf=' ';
		while (hurufBenar==false){
			printf("Pilih huruf S atau O = ");
			scanf(" %c", &huruf);
			if (huruf=='S' || huruf=='O' || huruf=='s' || huruf=='o'){
				hurufBenar=true;
			}
		}
	
		
		arr[row][col]=toupper(huruf);
	} while (cek_sos(row,col,f,toupper(huruf)));
	
	
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
		player1= player1 + sos;
		Gambar_Papan(n);
		printf("\n%s mendapatkan %d poin!\n",nama1, sos);
		if (!cek_papan())
		{
			end_game(mode_main);
		}
		else{
			printf("\n****************************************************************\nGiliran %s lagi!\n",nama1);
		}
	}
	else if (o == 2 && sos>0)
	{
		player2= player2 + sos;
		Gambar_Papan(n);
		printf("\n%s mendapatkan %d poin!\n",nama2, sos);
		if (!cek_papan())
		{
			end_game(mode_main);
		}
		else{
			printf("\n****************************************************************\nGiliran %s lagi!\n",nama2);
		}
	}
	
	else if (o == 3 && sos>0)
	{
		comp= comp + sos;
		Gambar_Papan(n);
		printf("\nComp mendapatkan %d poin!\n", sos);	
	}
	


	if (sos>0 && cek_papan())
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

void peraturan(){
	system("cls");
	printf("*  .\n\n");
	printf("!!! Hal Yang Perlu Dilakukan Sebelum Bermain !!!\n\n");
	printf("1) Memilih Mode Permainan\n   Di game SOS ini terdapat 3 mode permainan, yaitu Player vs Player, Player vs Computer, dan Player vs Player vs Computer.\n\n");
	printf("2) Memilih Tingkat Kesulitan Computer\n   Jika bermain melawan computer, player akan diminta untuk memilih tingkat kesulitan computer.\n   Tersedia 3 tingkat kesulitan computer: 1 = mudah, 2 = menengah, 3 = sulit.\n\n");
	printf("3) Menentukan Besar Papan Permainan\n   Player diminta untuk menentukan besar papan permainan. Pemain dapat bermain di papan permainan 3x3 sampai 15x15.\n\n");
	printf("*  .");
	printf("\n\n??? Aturan Bermain SOS ???\n\n");
	printf("1) Player/Player 1 memulai permainan.\n");
	printf("2) Player memilih kotak yang ingin diisi (Contoh: A1).\n");
	printf("3) Player memilih huruf 'S' atau 'O' untuk diisi di kotak yang dipilih.\n");
	printf("4) Player akan mendapat 1 poin jika berhasil menyusun kata 'SOS' secara vertikal, horizontal, maupun diagonal.\n");
	printf("5) Player bermain sesuai gilirannya.\n");
	printf("6) Kumpulkan poin lebih banyak dari lawan untuk memenangkan permainan!");
	printf("\n\n*  .");
	printf("\n\nKetik 0 untuk kembali ke menu utama = ");
}

void menu_utama(){
	printf("*  . Selamat datang di game SOS! .  * \n");
	fpointer=fopen("pemenang.txt", "r");
	fgets(Pemenang, 35, fpointer);
	fclose(fpointer);
	fpointer=fopen("highscore.txt", "r");
	fscanf(fpointer, "%d", &HighScore);
	fclose(fpointer);
	printf("\n  High Score = %s %d", Pemenang, HighScore);
	printf("\n\n  1 = Main\n  2 = Aturan Permainan\n  3 = Keluar");
	printf("\n\n   > Pilihanmu = ");
}
