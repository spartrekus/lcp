


// Source:
// "https://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux"

#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif


              #include <unistd.h>
              #include <sys/types.h>
              #include <dirent.h>
              #include <stdio.h>
              #include <string.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>


#include <stdio.h>
#include <stdlib.h>




#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>


              void listdir_basic(const char *name, int indent)
              {
                  DIR *dir;
                  struct dirent *entry;

                  if (!(dir = opendir(name)))
                      return;

                  while ((entry = readdir(dir)) != NULL) {
                      if (entry->d_type == DT_DIR) {
                char path[1024];
                 if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                      continue;
                          snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
                          printf("%*s[%s]\n", indent, "", entry->d_name);
                          listdir_basic(path, indent + 2);
                      } else {
                          printf("%*s- %s\n", indent, "", entry->d_name);
                      }
                  }
                  closedir(dir);
              }


#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>




/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR  *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}


//////////////////
void ncp( char *filetarget,  char *  filesource )
{
  // fread
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "wb");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) {
                freader = 0 ; 
            }
            n = fread(  buffer, sizeof(char), 1 , fp);
            m = fwrite( buffer, sizeof(char), 1,  fp2);
        }
        fclose(fp2);
        fclose(fp);
      }
}






char searchitem[PATH_MAX];
void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    char charo[PATH_MAX];
    char charotarget[PATH_MAX];

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);

              snprintf( charo, PATH_MAX , "%s/%s", name , entry->d_name );
              printf("===> DIR: %s",  charo ) ;
              printf(" (DIR: %d)", fexist( charo )) ;
              printf("\n");

           if ( fexist( "/uploads" ) == 2 )
           {
              snprintf( charo, PATH_MAX , "/uploads/%s/%s", name , entry->d_name );
              //mkdir( charo , "S_IRWXU" );
              //mkdir( charo , S_IRWXU );  notworking
              //mkdir(  charo , S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
              //mkdir( charo , ACCESSPERMS);
              mkdir( charo , 0777 );
              printf( "==> Create dir: %s\n", charo );
           }

           listdir( path, indent + 2);
        } 
	else 
	{
	    //if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {
              //printf("DIR %s\n", name );
              //printf("%*s- %s\n", indent, "", entry->d_name);
              printf("%s/%s", name , entry->d_name );
              snprintf( charo, PATH_MAX , "%s/%s", name , entry->d_name );
              snprintf( charotarget, PATH_MAX , "/uploads/%s/%s", name , entry->d_name );
              printf(" (File: %d)", fexist( charo )) ;
              printf("\n");
              printf( "  Source: %s\n", charo );
              printf( "  Target: %s\n", charotarget );
              printf( "  Copy (Start): %s => %s\n", charo ,  charotarget );
              ncp( charotarget, charo ); 
              printf( "  Copy (End): \n");
              printf( "-----  \n");
	    }
        }
    }
    closedir(dir);
}



int main( int argc, char *argv[])
{

    printf( "LCP \n" );
    int i ; 

    //if ( argc >= 2)
    //if ( strcmp( argv[ 1 ] , "--make"  ) == 0  ) 
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            //if ( fexist( argv[ i ] ) == 1 ) ntexmake( argv[ i ] , 1 );
          }


    if ( argc >= 2)
    if ( fexist( argv[ 1 ] ) == 2 ) 
      chdir( argv[ 1 ] );


                  listdir(".", 0);
                  //return 0;
              //}

   return 0;


   FILE *source, *target; int ch ; 
   source = fopen( argv[ 1 ], "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   target = fopen( argv[ 2 ] , "w");
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   printf("Source: %s\n",  argv[ 1 ] );
   printf("Target: %s\n",  argv[ 2 ] );
   printf("Copying...\n");

   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   printf("File copied successfully.\n");
   fclose(source);
   fclose(target);
   return 0;
}


/*
not working
mkdir("mydir", S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
mkdir("mydir", S_IRWXU | S_IRWXG | S_IRWXO);
mkdir("mydir", ACCESSPERMS);
*/

