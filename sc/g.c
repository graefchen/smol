#include <stdio.h> // sg -- generate a matrix file
typedef char C;typedef int I;typedef unsigned int U;typedef size_t T;typedef float f;typedef void V;typedef FILE F;
typedef struct {I h,s,m,n;}A;A h={0,1975,256,256};//basic arguments/global stored
#define R return
#define o(s,...) fprintf(s,__VA_ARGS__)
#define P(l) {if(i+1<c){I t=atoi(v[i+1]);l=t!=0?t:l;}i++;break;}
V*malloc(T a);V free(V*b);I atoi(C*s);
// rng -- from Numerical Recipes in C by W. H. Press, S. A. Teukolsky, W. T. Vetterling, B. P. Flannery -- quick & dirty
U z;V srng(I s){z=(U)s;}f rng(V){I t;z=z*0x19660D+0x3C6EF35F;t=z>>9|0x3F800000;R *(f*)&t-1.0f;}
inline V g(C*n){*n=(C)(rng()*256);}
V d(C*a,register size_t c){register I n=(c+7)/8;switch(c%8){case 0:do{g(a++);case 7:g(a++);
 case 6:g(a++);case 5:g(a++);case 4:g(a++);case 3:g(a++);case 2:g(a++);case 1:g(a++);}while(--n>0);}}
V r(I s,I m,I n,F*f){U t=m*n;C*mn=malloc(t);srng(s);d(mn,t);fwrite(mn,sizeof(C),t,f);free(mn);}
I p(I c,C**v){for(I i=1;i<c;i++){if(v[i][0]=='-'){switch(v[i][1]){case 'h':h.h=1;break;case 's':P(h.s);case 'm':P(h.m);
 case 'n':P(h.n);default:{o(stderr,"sg: unrecognized option '%s'\n",v[i]);R 1;break;}}}}R 0;}
V hp(V){o(stderr,"sg -- secrete generation\nusage: sg file [options]\noptions:\n  -h      help text"
 "\n  -m num  m dim of matrix\n  -n num  n dim of matrix\n  -s num  starting seed\n");}
I main(I c,C**v){F*f;I pf=p(c,v);if(c==1||h.h||pf){hp();}else{fopen_s(&f,v[1],"wb");
 if(f==NULL){o(stderr,"couldn't write file: %s",v[1]);}else{r(h.s,h.m,h.n,f);}fclose(f);}R 0;}