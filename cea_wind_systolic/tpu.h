#include "ap_int.h"

#define MXU_COLNUM 32
#define MXU_ROWNUM 32
#define WEIGHTDTYPE char
#define FEATDTYPE char
#define PSUMDTYPE int


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
	short psum_step1;
	short psum_end1;
	short psum_step2;
};
struct ACCREL_PARAM{
	bool isrelu;
	short psum_raddr_start;
	short psum_raddr_num;

	short ubuf_waddr_start;
	short ubuf_waddr_step1;
	short ubuf_waddr_step2;
	short ubuf_waddr_step3;
	short ubuf_waddr_end1;
	short ubuf_waddr_end2;
	short ubuf_waddr_end3;
};

void MXU(FEATDTYPE ubuf[16384][MXU_ROWNUM],WEIGHTDTYPE weight[512][MXU_COLNUM],
		PSUMDTYPE psum[512][MXU_COLNUM],MXU_PARAM mxuparam);
