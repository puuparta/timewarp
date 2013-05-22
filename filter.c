/* filter.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <jd_pretty.h>

#include "yuv4mpeg2.h"
#include "merge.h"
#include "minmax.h"
#include "streak.h"
#include "wobble.h"
#include "massive.h"

y4m2_output *filter_hook(const char *name, y4m2_output *out, jd_var *opt) {
  if (!strcmp("streak", name)) return streak_hook(out, opt);
  if (!strcmp("wobble", name)) return wobble_hook(out, opt);
  if (!strcmp("merge", name)) return merge_hook(out, opt);
  if (!strcmp("minmax", name)) return minmax_hook(out, opt);
  if (!strcmp("massive", name)) return massive_hook(out, opt);
  fprintf(stderr, "Unknown filter: %s\n", name);
  exit(1);
}

y4m2_output *filter_build(y4m2_output *out, jd_var *config) {
  y4m2_output *last_out = out;

  for (int i = jd_count(config); --i >= 0;) {
    jd_var *filt = jd_get_idx(config, i);
    last_out = filter_hook(jd_bytes(jd_lv(filt, "$.filter"), NULL),
                           last_out, jd_lv(filt, "$.options"));
  }

  return last_out;
}

/* vim:ts=2:sw=2:sts=2:et:ft=c
 */