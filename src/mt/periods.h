struct period {
  float p;
  int ns;
  float dt;
  int ld;
  int mt;
  struct period *next;
};

void mt_periods_free(struct period *p);

struct period *mt_periods_gen(float plower, float pupper, float rlkoz,
			      int m, float dt, float wave);

