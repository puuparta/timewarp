/* filter.h */

#ifndef FILTER_H_
#define FILTER_H_

#include <jd_pretty.h>

#include "yuv4mpeg2.h"

typedef struct filter filter;

typedef void (*filter_cb_start)(filter *filt,
                                const y4m2_parameters *parms);
typedef void (*filter_cb_frame)(filter *filt,
                                const y4m2_parameters *parms,
                                y4m2_frame *frame);
typedef void (*filter_cb_end)(filter *filt);

struct filter {
  filter_cb_start start;
  filter_cb_frame frame;
  filter_cb_end end;

  jd_var config;
  y4m2_output *out;
  void *ctx;
};

void filter_init(void);
y4m2_output *filter_hook(const char *name, y4m2_output *out, jd_var *opt);
y4m2_output *filter_build(y4m2_output *out, jd_var *config);
void filter_register(const char *name, filter *f);

#endif

/* vim:ts=2:sw=2:sts=2:et:ft=c
 */
