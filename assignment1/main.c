#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
int main(int argc, char* argv[]){
	int size;
	char err[6] = "error";
	int space[100];
	int fp = open(argv[1],O_RDONLY,0755);
	int temp1,idx1;
	char buffer[512];
	char sub[512];
	char strnum1[100];
	char readbuffer;
	int problemcase = 0;
	int inputsize = 0;
	int buffersize = 0;
	int line=0;
	int t;
	int l, r, idx;
	int star,temp;
	int check[2] = {-1, -1};
	int last_offset = lseek(fp,0,SEEK_END);
	lseek(fp,0,SEEK_SET);
	int pos =0;	
	while(1)
	{	
		char input[512];
		char c;
		inputsize = 0;
		
		read(STDIN_FILENO, &c, 1);
		do {
			input[inputsize++] = c;
			read(STDIN_FILENO, &c, 1);
		}while(c != '\n');

		input[inputsize] = '\0';
		//program exit condition
		if (inputsize == 7)
		{
			char ex[7] = "PA1EXIT";
			for(int i=0; i<7;i++)
			{
				if(input[i] != ex[i]) break;
				if(i == 6)
				{
				       close(fp);
			       	       return 0;
				}
			}
		}

		problemcase = 1;
		for(int i=0;i<inputsize;i++)
			if(input[i] > 64 && input[i] < 91) input[i] +=32;

		for(int i=0;i<inputsize;i++){
			if(input[i] == '\"'){
				problemcase = 3;
				
				for(int i=0;i<inputsize-2;i++)
				{
					input[i] = input[i+1];
				}
				input[inputsize - 1] = '\0';
				input[inputsize - 2] = '\0';	
				inputsize-=2;
				break;
			}
			else if(input[i] == '*'){
				problemcase = 4;
				star = i;
				break;
			}
			else if(input[i] == ' '){
				problemcase = 2;
				break;
			}
		}
		line=0;
		pos = 0;	
		switch(problemcase){
			case 1:
				while(pos < last_offset){
					buffersize=0;
					read(fp,&readbuffer,1);
					while(readbuffer != '\n')
					{
						buffer[buffersize] = readbuffer;
						buffersize++;
						pos++;
						if(pos == last_offset) break;
						read(fp,&readbuffer,1);
					}
					buffer[buffersize] = '\n';
					buffer[buffersize+1] = '\0';
					pos++;
					line++;
					buffersize=0;
					while(buffer[buffersize] != '\n') 
					{
						if(buffer[buffersize] > 64 && buffer[buffersize] < 91) buffer[buffersize] +=32;
						buffersize++;
					}
					l=0;
					while(buffersize > l)
					{	

						r = l;
						if(buffer[r] == input[0])
						{
							t=0;
							for(int i=1;i<inputsize;i++)
							{
								r++;
								if(buffersize < r) break;
								if(buffer[r] != input[i]){
									t = 1;       
									break;
								}
							}
							if ( t != 1 & (l == 0 | buffer[l-1] == ' ') & (buffer[r+1] == ' ' | buffer[r+1] == '\n') )
							{

								if(check[0]  < 0)
								{
									check[0] = line;
									check[1] = l;
								}
								else{
									temp1 = check[0];
               								idx1 = 0;
                							while(temp1){
										strnum1[idx1]=temp1%10+48;
                       							 	temp1/=10;
                   								idx1+=1; 
 									}
          								for(int k=0;k<idx1;k++){
                        							write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
                							}
									c = ':';
									write(STDOUT_FILENO, &c, 1);
									temp1 = check[1];
               								idx1 = 0;
                							while(temp1){
										strnum1[idx1]=temp1%10+48;
                       							 	temp1/=10;
                   								idx1+=1; 
 									}
									if(check[1] == 0){
										c = '0';
										write(STDOUT_FILENO, &c, 1);
									}
									else{

										for(int k=0;k<idx1;k++){
											write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
										}
									}
									c = ' ';
									write(STDOUT_FILENO,&c,1);
									check[0] = line;
									check[1] = l;
								}
								l++;
							
								
							}
							else l++;
						}
						else 
						{
							l++;
							
						}
					}
				}
				if(check[0] > 0)
				{
					temp1 = check[0];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}
					for(int k=0;k<idx1;k++){
						write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
					}
					c = ':';
					write(STDOUT_FILENO, &c, 1);
					temp1 = check[1];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}	
					if(check[1] == 0){
						c = '0';
						write(STDOUT_FILENO, &c, 1);
					}
					else{

						for(int k=0;k<idx1;k++){
							write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
						}
					}
					c = '\n';				
					write(STDOUT_FILENO, &c,1);

					check[0]=-1;
					check[1]=-1;
				}
				else {
					c = '\n';
					write(STDOUT_FILENO, &c,1);
				}
				lseek(fp,0,SEEK_SET);
				break;

			case 2:	
				idx=1;
				space[0] = -1;
				int su=0;
				for(int i=0;i<inputsize;i++)
				{
					if(input[i] == ' ') space[idx++] = i;
				}//space check idx =3 space = 2 firestvalue = -1
				space[idx] = inputsize;
				while(pos < last_offset)
				{
					buffersize=0;
					read(fp,&readbuffer,1);
					while(readbuffer != '\n')
					{
						buffer[buffersize] = readbuffer;
						buffersize++;
						pos++;
						if(pos == last_offset) break;
						read(fp,&readbuffer,1);
					}
					buffer[buffersize] = '\n';
					pos++;
					line++;
					buffersize=0;
					su = 0;
					t=0;
					while(buffer[buffersize] != '\n')
					{
						if(buffer[buffersize] > 64 && buffer[buffersize] < 91) buffer[buffersize] +=32;
						buffersize++;
					}
					
					for(int k=0;k<idx;k++)
					{
						l=0;
						if(buffersize == l){
							t=1;
						}
						while(buffersize > l)
						{	
						
							t=0;
							
							for(int i=space[k]+1;i<space[k+1];i++)
							{			
								
								if(buffer[l++] != input[i])
								{	
									t=1;
									while(buffer[l] != ' ' && buffersize > l) l++;
								        l++;	
									break;
								}
							
							}
							
							if ( t == 0) {
								if (buffer[l] == ' ' | buffer[l] == '\n')
								{	
									t=2;
									break;
								}			
							}
						}
						if ( t == 1) break;
						if( t == 2 ) su++;
					}
					if( su == idx ) {
						if(check[0] > 0)
							{
								temp1 = check[0];
								idx1 = 0;
								while(temp1){
									strnum1[idx1]=temp1%10+48;
									temp1/=10;
									idx1+=1; 
								}
								for(int k=0;k<idx1;k++){
									write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
								}
								c = ' ';
								write(STDOUT_FILENO,&c,1);
								check[0] = line;
							}
						else check[0] = line;
					}	
				}
				if(check[0] > 0)
				{	
					temp1 = check[0];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}
					for(int k=0;k<idx1;k++){
						write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
					}
					c = '\n';
					write(STDOUT_FILENO,&c,1);
					check[0]=-1;
				}
				else {
					c = '\n';
					write(STDOUT_FILENO,&c,1);
				}
				lseek(fp,0,SEEK_SET);
				break;


			case 3:
			
				while(pos < last_offset)
				{
					buffersize=0;
					read(fp,&readbuffer,1);
					while(readbuffer != '\n')
					{
						buffer[buffersize] = readbuffer;
						buffersize++;
						pos++;
						if(pos == last_offset) break;
						read(fp,&readbuffer,1);
					}
					buffer[buffersize] = '\n';
					pos++;
					line++;
					buffersize=0;
					while(buffer[buffersize] != '\n') 
					{
						if(buffer[buffersize] > 64 && buffer[buffersize] < 91) buffer[buffersize] +=32;
						buffersize++;
					}

					l=0;
					while(buffersize > inputsize - 1)
					{	
						r=1;
						if(buffer[l] == input[0])
						{
							t=0;
							for(int i=1;i<inputsize;i++)
							{
								r = l+i;
								if(buffer[r] != input[i]){
									t = 1;       
									break;
								}
							}
							
							if ( t != 1 & (l == 0 | buffer[l-1] == ' ') & (buffer[r+1] == ' ' | buffer[r+1] == '\n'))
							{
								if(check[0]  < 0)
								{
									check[0] = line;
									check[1] = l;
								}
								else{
									temp1 = check[0];
               								idx1 = 0;
                							while(temp1){
										strnum1[idx1]=temp1%10+48;
                       							 	temp1/=10;
                   								idx1+=1; 
 									}
          								for(int k=0;k<idx1;k++){
                        							write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
                							}
									c = ':';
									write(STDOUT_FILENO, &c, 1);
									temp1 = check[1];
               								idx1 = 0;
                							while(temp1){
										strnum1[idx1]=temp1%10+48;
                       							 	temp1/=10;
                   								idx1+=1; 
 									}	
									if(check[1] == 0){
										c = '0';
										write(STDOUT_FILENO, &c, 1);
									}
									else{

										for(int k=0;k<idx1;k++){
											write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
										}
									}
									c = ' ';
									write(STDOUT_FILENO,&c,1);
									check[0] = line;
									check[1] = l;
								}
								l++;
								buffersize--;
								
							}
							else l++;
						}
						else 
						{
							l++;
							buffersize--;
						}
					}


				}
				if(check[0] > 0)
				{
					temp1 = check[0];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}
					for(int k=0;k<idx1;k++){
						write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
					}
					c = ':';
					write(STDOUT_FILENO, &c, 1);
					temp1 = check[1];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}	
					if(check[1] == 0){
						c = '0';
						write(STDOUT_FILENO, &c, 1);
					}
					else{

						for(int k=0;k<idx1;k++){
							write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
						}
					}
					c = '\n';				
					write(STDOUT_FILENO, &c,1);

					check[0]=-1;
					check[1]=-1;
				}
				else {
					c = '\n';
					write(STDOUT_FILENO, &c,1);
				}
				lseek(fp,0,SEEK_SET);
				break;
			case 4:
	
				while(pos < last_offset)
				{	
					buffersize=0;
					read(fp,&readbuffer,1);
					while(readbuffer != '\n')
					{
						buffer[buffersize] = readbuffer;
						buffersize++;
						pos++;
						if(pos == last_offset) break;
						read(fp,&readbuffer,1);
					}
					buffer[buffersize] = '\n';
					pos++;
					line++;
					buffersize=0;
					while(buffer[buffersize] != '\n') 
					{
						if(buffer[buffersize] > 64 && buffer[buffersize] < 91) buffer[buffersize] +=32;
						buffersize++;
					}

					l=0;
					//we know star index
					while(buffersize > inputsize - 1)
					{	
						r=1;
						if(buffer[l] == input[0])
						{
							t=0;
							r=l;
							for(int i=1;i<star;i++)
							{	
								r++;
								if(buffer[r] != input[i]){
									t = 1;       
									break;
								}
								if(buffer[r+1] != ' '){
								    	 t=1;
							  	    	 break;
								}
							}
							if ( t != 1 )
							{	
								temp = r;
								temp+=2;
								while(buffersize > inputsize - star)
								{
									t=0;
									temp++;
									if(buffer[temp] ==  input[star+1] & buffer[temp-1] == ' ')
									{
										r = temp;
										for(int i = star +2; i<inputsize;i++){
											r++;
											if(buffer[r] != input[i]){
												t=1;
												break;
											}
										
										}
										if ( t==0 ) break;
									}
									else t=1;
									buffersize--;
								}
								
							}	
									
							
							if ( t != 1 & (l == 0 | buffer[l-1] == ' ') & (buffer[r+1] == ' ' | buffer[r+1] == '\n') )
							{
								if(check[0]  < 0)
								{
									check[0] = line;
								}
								else{	
									temp1 = check[0];
									idx1 = 0;
									while(temp1){
										strnum1[idx1]=temp1%10+48;
										temp1/=10;
										idx1+=1; 
									}
									for(int k=0;k<idx1;k++){
										write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
									}
									c = ' ';
									write(STDOUT_FILENO,&c,1);
									check[0] = line;
								}
								break;
								
								
								
							}
							else l++;
						}
						else 
						{
							l++;
							buffersize--;
						}
					}


				}
				if(check[0] > 0)
				{	
					temp1 = check[0];
					idx1 = 0;
					while(temp1){
						strnum1[idx1]=temp1%10+48;
						temp1/=10;
						idx1+=1; 
					}
					for(int k=0;k<idx1;k++){
						write(STDOUT_FILENO, &strnum1[idx1-1-k],1);
					}
					c = '\n';
					write(STDOUT_FILENO,&c,1);
					check[0]=-1;
				}
				else {
					c = '\n';
					write(STDOUT_FILENO,&c,1);
				}
				lseek(fp,0,SEEK_SET);
				break;

			default:
				for(int k=0;k<5;k++){
					write(STDOUT_FILENO, &err[k],1);
				}
				c = '\n';
				write(STDOUT_FILENO,&c,1);


		}

		
	}	
	return 0;
}
