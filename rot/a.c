#include <stdio.h> // rot -- a decently fast rot13 implementation, works only on files
typedef char C;typedef int I;typedef size_t T;typedef void V;typedef FILE F;
#define f(s,t) for(I i=s;i<t;i++)
#define o(s,...) fprintf(s,__VA_ARGS__)
#define R return
I strcmp(const C*a,const C*b);V*malloc(T a);V free(V*b);
inline V t(C*s){if(*s>=65&&*s<=90){*s+=*s<=77?13:-13;}else if(*s>=97&&*s<=122){*s+=*s<=109?13:-13;}}
C*a(F*f,T*s){fseek(f,0L,SEEK_END);*s=ftell(f);rewind(f);C*b=(C*)malloc(*s+1);T e=fread(b,sizeof(C),*s,f);b[e]='\0';R b;}
V r(C*s,register T c){register I n=(c+7)/8;switch(c%8){case 0:do{t(s++);case 7:t(s++);// duffs device
  case 6:t(s++);case 5:t(s++);case 4:t(s++);case 3:t(s++);case 2:t(s++);case 1:t(s++);}while(--n>0);}}
V n(F*f){C*d;T s;d=a(f,&s);r(d,s);o(stdout,"%s\n",d);free(d);}
I main(I c,C**v){if(c<=1){o(stderr,"usage: rot file");R 1;}f(1,c){F*f;fopen_s(&f,v[i],"r");
  if(f==NULL){o(stderr,"couldn't read file: %s\n",v[i]);}n(f);fclose(f);}R 0;}