#include "tpu.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


using namespace std;



#include <typeinfo>


int main(){
	FEATDTYPE ubuf[16384][MXU_ROWNUM];
	WEIGHTDTYPE weight[512][MXU_COLNUM];
	int psum[512][MXU_COLNUM];
	FILE *fid,*fid1 ,*fid2,*fid3,*fid4;
	fid = fopen("feature.dat","rb");
	fid4 = fopen("feature.txt","w");

	for(int i=0;i<14*14;i++){
		for(int j=0;j<32;j++){
			char a1[16]={0};
			int a;
			fread(&a,sizeof(int),1,fid);
			ubuf[i][j]=a;
			cout << a << endl;
			sprintf(a1,"%d",a);
			fputs(a1, fid4) ;
			fputs("\n",fid4);
		}
	}
	//cout << typeid(a).name() << endl;
	fclose(fid);
	fid = fopen("weight.dat","rb");
	fid3 = fopen("weight.txt","w");
	for(int i=0;i<3*3*32+32;i++){
		for(int j=0;j<32;j++){
			char a1[16]={0};
			int a;
			fread(&a,sizeof(int),1,fid);
			weight[i][j] = a;
			//fwrite(&a, sizeof(int),1,fid3) ;
			//cout << a << endl;
			sprintf(a1,"%d",a);
			fputs(a1, fid3) ;
			fputs("\n",fid3);
		}
	}
	fclose(fid);
	MXU_PARAM mxuparam;
	struct MXU_PARAM{
		bool isload;
		bool iscalc;
		bool isping;
		bool isfirstpsum;

		short weight_raddr;
		short ubuf_raddr_start;
		short ubuf_raddr_step1;
		short ubuf_raddr_step2;
		short ubuf_raddr_step3;
		short ubuf_raddr_end1;
		short ubuf_raddr_end2;
		short ubuf_raddr_end3;
		short ubuf_raddr_num;
		short psum_start;

	};//for(int i=0;i<14*14;i++){
		//for(int j=0;j<32;j++){

	mxuparam.isload = true;
	mxuparam.iscalc = false;
	mxuparam.isping = true;
	mxuparam.weight_raddr = 0;
	MXU(ubuf,weight,psum,mxuparam);
// 2,2
	mxuparam.weight_raddr = 36;
	mxuparam.iscalc = true;
	mxuparam.isping = false;
	mxuparam.isfirstpsum = true;
	mxuparam.ubuf_raddr_start = 0;
	mxuparam.ubuf_raddr_num = 14*14;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 14-1;
	mxuparam.ubuf_raddr_end2 = 14-1;
	mxuparam.psum_start = 0;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 13;
	//mxuparam.pfor(int i=0;i<14*14;i++){
	//	for(int j=0;j<32;j++){sum_step2 = 14;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);

//1,1
	mxuparam.weight_raddr = 36*2;
	mxuparam.iscalc = true;
	mxuparam.isping = true;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 0;
	mxuparam.ubuf_raddr_num = 13*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	mxuparam.ubuf_raddr_end2 = 14*13-1;
	mxuparam.psum_start = 15;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 =14;
	MXU(ubuf,weight,psum,mxuparam);
//1,2
	mxuparam.weight_raddr = 36*3;
	mxuparam.iscalc = true;
	mxuparam.isping = false;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 0;
	mxuparam.ubuf_raddr_num = 14*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 14-1;
	//mxuparam.ubuf_raddr_endsizeof(int)2 = 14*13-1;
	mxuparam.ubuf_raddr_end2 = 14*13-1;
	mxuparam.psum_start = 14;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 13;
	//mxuparam.psum_step2sizeof(int) = 14;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);
//1,3for(int i=0;i<14*14;i++){
	//for(int j=0;j<32;j++){
	mxuparam.weight_raddr = 36*4;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 1;
	mxuparam.ubuf_raddr_num = 13*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	mxuparam.ubuf_raddr_end2 = 13*13-1;
	mxuparam.psum_start = 14;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);
//2,1
	mxuparam.weight_raddr = 36*5;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 0;
	mxuparam.ubuf_raddr_num = 14*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	//mxuparam.ufor(int i=0;i<14*14;i++){
	//	for(int j=0;j<32;j++){buf_raddr_end2 = 14*13-1;
	mxuparam.ubuf_raddr_end2 = 14*13-1;
	mxuparam.psum_start = 1;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);


//2,3
	mxuparam.weight_raddr = 36*6;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 1;
	mxuparam.ubuf_raddr_num = 14*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	mxuparam.ubuf_raddr_end2 = 14*13-1;
	mxuparam.psum_start = 0;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);

//3,1
	mxuparam.weight_raddr = 36*7;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 14;
	mxuparam.ubuf_raddr_num = 13*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	mxuparam.ubuf_raddr_end2 = 13*13-1;
	mxuparam.psum_start = 1;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);

//3,2
	mxuparam.weight_raddr = 36*8;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 14;
	mxuparam.ubuf_raddr_num = 14*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	//mxuparam.ufor(int i=0;i<14*14;i++){
	//	for(int j=0;j<32;j++){buf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 14-1;
	mxuparam.ubuf_raddr_end2 = 14*13-1;
	mxuparam.psum_start = 0;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 13;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);

//3,3
	mxuparam.isload = false;
	mxuparam.iscalc = true;
	mxuparam.isping = !mxuparam.isping;
	mxuparam.isfirstpsum = false;
	mxuparam.ubuf_raddr_start = 15;
	mxuparam.ubuf_raddr_num = 13*13;
	mxuparam.ubuf_raddr_step1 = 1;
	mxuparam.ubuf_raddr_step2 = 14;
	mxuparam.ubuf_raddr_step3 = 1;
	mxuparam.ubuf_raddr_end1 = 13-1;
	mxuparam.ubuf_raddr_end2 = 13*13-1;
	mxuparam.psum_start = 0;
	mxuparam.psum_step1 = 1;
	mxuparam.psum_end1 = 12;
	mxuparam.psum_step2 = 14;
	MXU(ubuf,weight,psum,mxuparam);
    fid1 = fopen("debug.txt","w") ;
    for(int i=0;i<14*14;i++){
    		for(int j=0;j<32;j++){
    			char a1[16]={0};
    			int v;
    			v=psum[i][j];
    		//fwrite(&v,sizeof(int),1,fid1);
    		//cout << v << endl;
    		sprintf(a1,"%d",v);
    		fputs(a1, fid1) ;
    		fputs("\n",fid1);
    	    }
    }
	int err = 0;
	fid = fopen("golden.dat","rb");
	fid2 = fopen("golden.text","w");
	for(int i=0;i<14*14;i++){
		for(int j=0;j<32;j++){
			char a1[16]={0};
			int a;
			fread(&a,sizeof(int),1,fid);
			if(psum[i][j] != a)
				err++;
			a = psum[i][j];
		//cout << a << endl;
        //fwrite(&a, sizeof(int),1,fid2) ;
		sprintf(a1,"%d",a);
		fputs(a1, fid2) ;
		fputs("\n",fid2);




		}

	}






	return 0;
}
