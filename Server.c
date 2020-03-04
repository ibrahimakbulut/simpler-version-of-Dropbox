#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>



int postOrderApplydelete(char *dirName,char *justdirname,int socket){





	char basePath[200];
	strcpy(basePath,dirName);

	char path[300];   //for travel in client side
    char justdirName[200];
	struct stat stat_buffer;
	struct dirent *dp;

	DIR *dir = opendir(basePath);




    char directory_info[200];
    memset(directory_info,'\0',200*sizeof(char));

    strcpy(directory_info,"1 ");
    strcat(directory_info,"0 ");
    strcat(directory_info,justdirname);
    //printf("%d\n",);
    send(socket,directory_info,200,0);

    char removed_known[200];
    memset(removed_known,'\0',200*sizeof(char));

    recv(socket,removed_known,200,0);

    if(strcmp(removed_known,"silindi")==0){
    	remove(basePath);
    }


    else{
	if (dir==NULL) {
    	printf("unable to open given source directort-------\n");
	}
		
    while ((dp = readdir(dir)) != NULL)
    {
	

	        memset(path,'\0',300*sizeof(char));
            memset(justdirName,'\0',200*sizeof(char));
            strcpy(path, basePath);
            strcat(path, "/");
            strcpy(justdirName, justdirname);
            strcat(justdirName, "/");
            strcat(path, dp->d_name);
            strcat(justdirName, dp->d_name);
            
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            
	 	
	    if (lstat(path, &stat_buffer) ==0){
	    if(S_ISDIR(stat_buffer.st_mode)){



	    	
			postOrderApply(path,justdirName,socket);
    
		}
        else if(S_ISREG(stat_buffer.st_mode)){  //if file is a regular file

            char size[10];

            memset(size,'\0',10*sizeof(char));

            sprintf(size,"%d",(int)stat_buffer.st_size);


			memset(directory_info,'\0',200*sizeof(char));
            strcpy(directory_info,"2 ");
            strcat(directory_info,size);
            strcat(directory_info," ");
            strcat(directory_info,justdirName);
            //printf("%s\n",justdirName);
            //printf("%s\n",dp->d_name);
           // printf("%s\n",directory_info);
            //printf("%s\n",directory_info);
            //printf("%d\n",);
            send(socket,directory_info,200,0);

               memset(removed_known,'\0',200*sizeof(char));
               recv(socket,removed_known,200,0);

    		if(strcmp(removed_known,"silindi")==0){
    			remove(path);
		    }


         }
	   }
		}

    }

	}
 	closedir(dir);
} 	

int postOrderApply(char *dirName,char *justdirname,int socket){

    printf("buralara giriyor\n");


	char basePath[200];
	strcpy(basePath,dirName);

	char path[300];   //for travel in client side
    char justdirName[200];
	struct stat stat_buffer;
	struct dirent *dp;

	DIR *dir = opendir(basePath);




    char directory_info[200];
    memset(directory_info,'\0',200*sizeof(char));

    strcpy(directory_info,"1 ");
    strcat(directory_info,"0 ");
    strcat(directory_info,justdirname);
    //printf("%d\n",);
    send(socket,directory_info,200,0);


	if (dir==NULL) {
    	printf("unable to open given source directort\n");
	}
		
    while ((dp = readdir(dir)) != NULL)
    {
	

	        memset(path,'\0',300*sizeof(char));
            memset(justdirName,'\0',200*sizeof(char));
            strcpy(path, basePath);
            strcat(path, "/");
            strcpy(justdirName, justdirname);
            strcat(justdirName, "/");
            strcat(path, dp->d_name);
            strcat(justdirName, dp->d_name);
            
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            
	 	
	    if (lstat(path, &stat_buffer) ==0){
	    if(S_ISDIR(stat_buffer.st_mode)){



	    	
			postOrderApply(path,justdirName,socket);
    
		}
        else if(S_ISREG(stat_buffer.st_mode)){  //if file is a regular file

            char size[10];

            memset(size,'\0',10*sizeof(char));

            sprintf(size,"%d",(int)stat_buffer.st_size);


memset(directory_info,'\0',200*sizeof(char));
            strcpy(directory_info,"2 ");
            strcat(directory_info,size);
            strcat(directory_info," ");
            strcat(directory_info,justdirName);
            //printf("%s\n",justdirName);
            //printf("%s\n",dp->d_name);
           // printf("%s\n",directory_info);
            //printf("%s\n",directory_info);
            //printf("%d\n",);
            send(socket,directory_info,200,0);

            int fd=open(path,O_RDONLY,0777);


            int bytes_read=10;

             char buf[200];
             memset(buf,'\0',sizeof(char)*200);
             while((bytes_read = read(fd,buf,200)) !=0 && bytes_read!=-1){

                //printf("%s\n",buf);

                send(socket,buf,200,0);

                 memset(buf,'\0',sizeof(char)*200);



             }

             close(fd);

        	


        	/*int fd2=open(destpath,O_CREAT | O_TRUNC | O_WRONLY,0777);



        	 char sfd[10];
        	 char sfd2[10];

        	 memset(sfd,'\0',10*sizeof(char));
        	 memset(sfd2,'\0',10*sizeof(char));

        	 sprintf(sfd,"%d",fd);
        	 sprintf(sfd2,"%d",fd2);


             sem_wait(&buffer_empty);

        	 sem_wait(&writing_buffer);  //writing to buffer starts here

        	 sem_wait(&printing);  //printing to output is syncronize
        	if(fd<0){
        		printf("Error in opening for reading file");    //writing to standart output.this should be syncronize with consumers
        		close(fd);
        		close(fd2);
        	}
        	 if(fd2<0){
        	 	printf("Error in opening for writing to destination file");  
        	 	close(fd);
        	 	close(fd2); 
        	 }     	


        	 memset(buffer[buf_size],'\0',MAX_BUFFER_SIZE*sizeof(char));


        	 strcpy(buffer[buf_size],sfd);
        	 strcat(buffer[buf_size]," ");
        	 strcat(buffer[buf_size],sfd2);
        	 strcat(buffer[buf_size]," ");
        	 strcat(buffer[buf_size],dp->d_name);
        	 buf_size+=1;


        	 sem_post(&printing);
        	 sem_post(&writing_buffer);

        	 sem_post(&buffer_full);
	    }
	    else if(S_ISFIFO(stat_buffer.st_mode)){  //if file is a fifo then just copy the skeleton
	    	mkfifo(destpath,0777);            
	    }*/
         }
	   }
		}
		// free(path);

		// free(destpath);
		// free(src_and_dest[0]);
		// free(src_and_dest[1]);
    }

    //free(basePath);
    //free(dest);
	
 	closedir(dir);

} 


int main(int argc,char **argv){


	/*if(argc!=4){
		printf("Usage: BibakBOXServer --directory-- --threadPoolsize-- --portnumber--\n");
		exit(-1);
	}*/

	unsigned short portnum=5000;


	char myname[100];
	int s;
	struct sockaddr_in sa;

	memset(&sa,0,sizeof(struct sockaddr_in));


	sa.sin_family=AF_INET;
	sa.sin_port=htons(portnum);
	sa.sin_addr.s_addr=inet_addr("192.168.70.129");

	if((s=socket(AF_INET,SOCK_STREAM,0))<0)
		return -1;
	if(setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&(int){1},sizeof(int))<0){
		printf("socket error");
		return -1;
	}

	if(bind(s,(struct sockaddr *)&sa,sizeof(struct sockaddr_in))<0){
		close(s);
		return -1;
	}
	listen(s,3);

	char ServerSide[200];
	strcpy(ServerSide,argv[1]);

	int a=accept(s,NULL,NULL);

	char clientDir[200];
	memset(clientDir,'\0',200*sizeof(char));
	char path[300];   //for travel in client side
	struct stat stat_buffer;
	struct dirent *dp;

	DIR *dir = opendir(ServerSide);


	int c=recv(a,clientDir,200,0);

	printf("okumada no problem\n");

	int exist_flag=0;


	if (dir==NULL) {
    	printf("unable to open given source directort\n");
	}
		
    while ((dp = readdir(dir)) != NULL)
    {
	
	        memset(path,'\0',300*sizeof(char));
            strcpy(path, ServerSide);
 
            strcat(path, "/");
            strcat(path, dp->d_name);
            
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
            
	 	
	    if (lstat(path, &stat_buffer) ==0){
	    if(S_ISDIR(stat_buffer.st_mode)){

	    	if(strcmp(dp->d_name,clientDir)==0){
	    		printf("offfff\n");
	    		send(a,"exist",100,0);
	    		exist_flag=1;
	    		break;
	    	}
		}

    	}
		}
	}
	if(exist_flag==0){
		send(a,"nexist",100,0);
	}
	if(!exist_flag){
		printf("abooooooo\n");
		int file_type;
		int size_of_file;
		char file_name[200];
		char file_info[200];

		//int b=0;
		while(1){


		memset(file_info,'\0',200*sizeof(char));
		memset(file_name,'\0',200*sizeof(char));

		

		printf("hephup\n");
		printf("%d\n",recv(a,file_info,200,0));

		printf("%s\n",file_info);

		sscanf(file_info,"%d %d %s",&file_type,&size_of_file,file_name);

		printf("%s\n",file_name);
		printf("%d\n",file_name[0]);
		printf("%d\n",size_of_file);

		if(file_type==5)
			break;

		int readen_size=-2;
		int total_size=0;

		char buf[200];
		memset(buf,'\0',200*sizeof(char));


		char destination[200];
		strcpy(destination,argv[1]);
		strcat(destination,"/");
		strcat(destination,file_name);

		if(file_type==1){

			mkdir(destination,0777);
		}
		else{
			//printf("%s file\n",file_name);
			//printf("%s\n",destination);
			int fd=open(destination,O_CREAT | O_TRUNC | O_WRONLY,0777);
			if(fd<0)
				printf("hataa\n");

			//printf("%d\n",);
			if(size_of_file!=0){
			while((readen_size=recv(a,buf,200,0))!=0 && readen_size!=-1){

				//printf("haaahhahahahhahah\n");

				char data[200];
				memset(data,'\0',200*sizeof(char));

				//printf("\0\0");
			//	printf("hahaahaha\n");

				if(size_of_file>200){
				write(fd,buf,200);
				size_of_file-=200;
				}
				else{
					write(fd,buf,size_of_file);
					break;
				}
				//printf("%s--%d\n",buf,strlen(buf));
				memset(buf,'\0',200*sizeof(char));
				//total_size+=readen_size;
			}
			}
		}
		//++b;

		}


		while(1){

        //int b=0;
        while(1){


        memset(file_info,'\0',200*sizeof(char));
        memset(file_name,'\0',200*sizeof(char));

        

        printf("hephup\n");
        printf("%d\n",recv(a,file_info,200,0));

        printf("%s\n",file_info);

        sscanf(file_info,"%d %d %s",&file_type,&size_of_file,file_name);

        printf("%s\n",file_name);
        printf("%d\n",file_name[0]);
        printf("%d\n",size_of_file);

        if(file_type==-505)
            break;

        int readen_size=-2;
        int total_size=0;

        char buf[200];
        memset(buf,'\0',200*sizeof(char));


      /*  int i=0;
        while(1){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }*/
        int i=0;
        while(i<strlen(file_name)){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }  

        char destination[200];
        memset(destination,'\0',200);
        strcpy(destination,argv[1]);
        strcat(destination,"/");
        strcat(destination,file_name);

        struct stat stat_buf;
        int flag=stat(destination,&stat_buf);

        if(file_type==1 && flag==-1){

            mkdir(destination,0777);
        }
        else if(file_type==2){
            printf("%s file\n",file_name);
            printf("%s\n",destination);
            //printf("%s\n",destination);
            int fd;
            if(flag==-1){
            fd=open(destination,O_CREAT | O_TRUNC | O_WRONLY,0777);
            if(fd<0)
                printf("hataa\n");
            }

            //printf("%d\n",);
            if(size_of_file!=0){
            while((readen_size=recv(a,buf,200,0))!=0 && readen_size!=-1){

                //printf("haaahhahahahhahah\n");

                char data[200];
                memset(data,'\0',200*sizeof(char));

                //printf("\0\0");
            //  printf("hahaahaha\n");

                if(size_of_file>200){
                if(flag==-1)
                    write(fd,buf,200);
                size_of_file-=200;
                }
                else{
                    if(flag==-1)
                        write(fd,buf,size_of_file);
                    break;
                }
                //printf("%s--%d\n",buf,strlen(buf));
                memset(buf,'\0',200*sizeof(char));
                //total_size+=readen_size;
            }
            }
        }
        //++b;

        }


        while(1){


        memset(file_info,'\0',200*sizeof(char));
        memset(file_name,'\0',200*sizeof(char));


        long modification_date;

        

        printf("hephup\n");
        printf("%d\n",recv(a,file_info,200,0));

        printf("%s\n",file_info);

        sscanf(file_info,"%d %d %s %ld",&file_type,&size_of_file,file_name,&modification_date);

        printf("%s\n",file_name);
        printf("%d\n",file_name[0]);
        printf("%d\n",size_of_file);

        if(file_type==-505)
            break;

        int readen_size=-2;
        int total_size=0;

        char buf[200];
        memset(buf,'\0',200*sizeof(char));

        char destination[200];
        memset(destination,'\0',200*sizeof(char));
        strcpy(destination,argv[1]);
        strcat(destination,"/");
        strcat(destination,file_name);

        struct stat stat_buf;
        int flag=stat(destination,&stat_buf);

         if(file_type==2){
            printf("%s file\n",file_name);
            printf("%s\n",destination);
            //printf("%s\n",destination);
            int fd;
            if(stat_buf.st_mtime<modification_date){
            fd=open(destination,O_CREAT | O_TRUNC | O_WRONLY,0777);
            if(fd<0)
                printf("hataa\n");
            }

            //printf("%d\n",);
            if(size_of_file!=0){
            while((readen_size=recv(a,buf,200,0))!=0 && readen_size!=-1){

                //printf("haaahhahahahhahah\n");

                char data[200];
                memset(data,'\0',200*sizeof(char));

                //printf("\0\0");
            //  printf("hahaahaha\n");

                if(size_of_file>200){
                if(stat_buf.st_mtime<modification_date)
                    write(fd,buf,200);
                size_of_file-=200;
                }
                else{
                    if(stat_buf.st_mtime<modification_date)
                        write(fd,buf,size_of_file);
                    break;
                }
                //printf("%s--%d\n",buf,strlen(buf));
                memset(buf,'\0',200*sizeof(char));
                //total_size+=readen_size;
            }
            }
        }

        //++b;

        }

		}



	}
	else{

		printf("offff ulan offfff\n");

		int i=0;
		int last_slash_count=0;
		while(argv[1][i]!='\0'){

		if(argv[1][i]=='/')
		last_slash_count=i;

		++i;

		}


		postOrderApply(strcat(strcat(argv[1],"/"),clientDir),clientDir,a);
		char message[200];
		memset(message,'\0',200*sizeof(char));

		strcpy(message,"5 ");
		strcat(message,"0 ");
		strcat(message,"copy_process_is_finished");
		send(a,message,200,0);


		while(1){

        int file_type;
        int size_of_file;
        char file_name[200];
        char file_info[200];

        //int b=0;
        while(1){


        memset(file_info,'\0',200*sizeof(char));
        memset(file_name,'\0',200*sizeof(char));

        

        printf("hephup\n");
        printf("%d\n",recv(a,file_info,200,0));

        printf("%s\n",file_info);

        sscanf(file_info,"%d %d %s",&file_type,&size_of_file,file_name);

        printf("%s\n",file_name);
        printf("%d\n",file_name[0]);
        printf("%d\n",size_of_file);

        if(file_type==-505)
            break;

        int readen_size=-2;
        int total_size=0;

        char buf[200];
        memset(buf,'\0',200*sizeof(char));


      /*  int i=0;
        while(1){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }*/
        int i=0;
        while(1){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }

        char destination[200];
        strcpy(destination,argv[1]);
        strcat(destination,"/");
        strcat(destination,&file_name[i+1]);

        struct stat stat_buf;
        int flag=stat(destination,&stat_buf);

        if(file_type==1 && flag==-1){

            mkdir(destination,0777);
        }
        else if(file_type==2){
            printf("%s file\n",file_name);
            printf("%s\n",destination);
            //printf("%s\n",destination);
            int fd;
            if(flag==-1){
            fd=open(destination,O_CREAT | O_TRUNC | O_WRONLY,0777);
            if(fd<0)
                printf("hataa\n");
            }

            //printf("%d\n",);
            if(size_of_file!=0){
            while((readen_size=recv(a,buf,200,0))!=0 && readen_size!=-1){

                //printf("haaahhahahahhahah\n");

                char data[200];
                memset(data,'\0',200*sizeof(char));

                //printf("\0\0");
            //  printf("hahaahaha\n");

                if(size_of_file>200){
                if(flag==-1)
                    write(fd,buf,200);
                size_of_file-=200;
                }
                else{
                    if(flag==-1)
                        write(fd,buf,size_of_file);
                    break;
                }
                //printf("%s--%d\n",buf,strlen(buf));
                memset(buf,'\0',200*sizeof(char));
                //total_size+=readen_size;
            }
            }
        }
        //++b;

        }



        while(1){


        memset(file_info,'\0',200*sizeof(char));
        memset(file_name,'\0',200*sizeof(char));


        long modification_date;

        

        printf("hephup\n");
        printf("%d\n",recv(a,file_info,200,0));

        printf("%s\n",file_info);

        sscanf(file_info,"%d %d %s %ld",&file_type,&size_of_file,file_name,&modification_date);

        printf("%s\n",file_name);
        printf("%d\n",file_name[0]);
        printf("%d\n",size_of_file);

        if(file_type==-505)
            break;

        int readen_size=-2;
        int total_size=0;

        char buf[200];
        memset(buf,'\0',200*sizeof(char));


      /*  int i=0;
        while(1){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }*/
        int i=0;
        while(1){
            if(file_name[i]=='/'){
                break;
            }
            ++i;
        }

        char destination[200];
        memset(destination,'\0',200*sizeof(char));
        strcpy(destination,argv[1]);
        strcat(destination,"/");
        strcat(destination,&file_name[i+1]);

        struct stat stat_buf;
        int flag=stat(destination,&stat_buf);

        //if(file_type==1 && flag==-1){

        //    mkdir(destination,0777);
      //  }
         if(file_type==2){
            printf("%s file\n",file_name);
            printf("%s\n",destination);
            //printf("%s\n",destination);
            int fd;
            if(stat_buf.st_mtime<modification_date){
            fd=open(destination,O_CREAT | O_TRUNC | O_WRONLY,0777);
            if(fd<0)
                printf("hataa\n");
            }

            //printf("%d\n",);
            if(size_of_file!=0){
            while((readen_size=recv(a,buf,200,0))!=0 && readen_size!=-1){

                //printf("haaahhahahahhahah\n");

                char data[200];
                memset(data,'\0',200*sizeof(char));

                //printf("\0\0");
            //  printf("hahaahaha\n");

                if(size_of_file>200){
                if(stat_buf.st_mtime<modification_date)
                    write(fd,buf,200);
                size_of_file-=200;
                }
                else{
                    if(stat_buf.st_mtime<modification_date)
                        write(fd,buf,size_of_file);
                    break;
                }
                //printf("%s--%d\n",buf,strlen(buf));
                memset(buf,'\0',200*sizeof(char));
                //total_size+=readen_size;
            }
            }
        }

        //++b;

        }

		}


	}


	close(a);









}








