#include <string.h>

#include "thread_options.h"

static void string_to_cpu(char **dst, const uint8_t *src)
{
	const char *__src = (const char *) src;

	if (strlen(__src))
		*dst = strdup(__src);
}

static void string_to_net(uint8_t *dst, const char *src)
{
	if (src)
		strcpy((char *) dst, src);
	else
		dst[0] = '\0';
}

void convert_thread_options_to_cpu(struct thread_options *o,
				   struct thread_options_pack *top)
{
	int i, j;

	string_to_cpu(&o->description, top->description);
	string_to_cpu(&o->name, top->name);
	string_to_cpu(&o->directory, top->directory);
	string_to_cpu(&o->filename, top->filename);
	string_to_cpu(&o->opendir, top->opendir);
	string_to_cpu(&o->ioengine, top->ioengine);
	string_to_cpu(&o->mmapfile, top->mmapfile);
	string_to_cpu(&o->read_iolog_file, top->read_iolog_file);
	string_to_cpu(&o->write_iolog_file, top->write_iolog_file);
	string_to_cpu(&o->bw_log_file, top->bw_log_file);
	string_to_cpu(&o->lat_log_file, top->lat_log_file);
	string_to_cpu(&o->iops_log_file, top->iops_log_file);
	string_to_cpu(&o->replay_redirect, top->replay_redirect);
	string_to_cpu(&o->exec_prerun, top->exec_prerun);
	string_to_cpu(&o->exec_postrun, top->exec_postrun);
	string_to_cpu(&o->ioscheduler, top->ioscheduler);
	string_to_cpu(&o->profile, top->profile);
	string_to_cpu(&o->cgroup, top->cgroup);

	o->td_ddir = le32_to_cpu(top->td_ddir);
	o->rw_seq = le32_to_cpu(top->rw_seq);
	o->kb_base = le32_to_cpu(top->kb_base);
	o->ddir_seq_nr = le32_to_cpu(top->ddir_seq_nr);
	o->ddir_seq_add = le64_to_cpu(top->ddir_seq_add);
	o->iodepth = le32_to_cpu(top->iodepth);
	o->iodepth_low = le32_to_cpu(top->iodepth_low);
	o->iodepth_batch = le32_to_cpu(top->iodepth_batch);
	o->iodepth_batch_complete = le32_to_cpu(top->iodepth_batch_complete);
	o->size = le64_to_cpu(top->size);
	o->size_percent = le32_to_cpu(top->size_percent);
	o->fill_device = le32_to_cpu(top->fill_device);
	o->file_size_low = le64_to_cpu(top->file_size_low);
	o->file_size_high = le64_to_cpu(top->file_size_high);
	o->start_offset = le64_to_cpu(top->start_offset);

	for (i = 0; i < DDIR_RWDIR_CNT; i++) {
		o->bs[i] = le32_to_cpu(top->bs[i]);
		o->ba[i] = le32_to_cpu(top->ba[i]);
		o->min_bs[i] = le32_to_cpu(top->min_bs[i]);
		o->max_bs[i] = le32_to_cpu(top->max_bs[i]);
		o->bssplit_nr[i] = le32_to_cpu(top->bssplit_nr[i]);

		if (o->bssplit_nr[i]) {
			o->bssplit[i] = malloc(o->bssplit_nr[i] * sizeof(struct bssplit));
			for (j = 0; j < o->bssplit_nr[i]; j++) {
				o->bssplit[i][j].bs = le32_to_cpu(top->bssplit[i][j].bs);
				o->bssplit[i][j].perc = le32_to_cpu(top->bssplit[i][j].perc);
			}
		}

		o->rwmix[i] = le32_to_cpu(top->rwmix[i]);
		o->rate[i] = le32_to_cpu(top->rate[i]);
		o->ratemin[i] = le32_to_cpu(top->ratemin[i]);
		o->rate_iops[i] = le32_to_cpu(top->rate_iops[i]);
		o->rate_iops_min[i] = le32_to_cpu(top->rate_iops_min[i]);
	}

	o->ratecycle = le32_to_cpu(top->ratecycle);
	o->nr_files = le32_to_cpu(top->nr_files);
	o->open_files = le32_to_cpu(top->open_files);
	o->file_lock_mode = le32_to_cpu(top->file_lock_mode);
	o->lockfile_batch = le32_to_cpu(top->lockfile_batch);
	o->odirect = le32_to_cpu(top->odirect);
	o->invalidate_cache = le32_to_cpu(top->invalidate_cache);
	o->create_serialize = le32_to_cpu(top->create_serialize);
	o->create_fsync = le32_to_cpu(top->create_fsync);
	o->create_on_open = le32_to_cpu(top->create_on_open);
	o->create_only = le32_to_cpu(top->create_only);
	o->end_fsync = le32_to_cpu(top->end_fsync);
	o->pre_read = le32_to_cpu(top->pre_read);
	o->sync_io = le32_to_cpu(top->sync_io);
	o->verify = le32_to_cpu(top->verify);
	o->do_verify = le32_to_cpu(top->do_verify);
	o->verifysort = le32_to_cpu(top->verifysort);
	o->verifysort_nr = le32_to_cpu(top->verifysort_nr);
	o->experimental_verify = le32_to_cpu(top->experimental_verify);
	o->verify_interval = le32_to_cpu(top->verify_interval);
	o->verify_offset = le32_to_cpu(top->verify_offset);

	memcpy(o->verify_pattern, top->verify_pattern, MAX_PATTERN_SIZE);

	o->verify_pattern_bytes = le32_to_cpu(top->verify_pattern_bytes);
	o->verify_fatal = le32_to_cpu(top->verify_fatal);
	o->verify_dump = le32_to_cpu(top->verify_dump);
	o->verify_async = le32_to_cpu(top->verify_async);
	o->verify_batch = le32_to_cpu(top->verify_batch);
	o->use_thread = le32_to_cpu(top->use_thread);
	o->unlink = le32_to_cpu(top->unlink);
	o->do_disk_util = le32_to_cpu(top->do_disk_util);
	o->override_sync = le32_to_cpu(top->override_sync);
	o->rand_repeatable = le32_to_cpu(top->rand_repeatable);
	o->use_os_rand = le32_to_cpu(top->use_os_rand);
	o->log_avg_msec = le32_to_cpu(top->log_avg_msec);
	o->norandommap = le32_to_cpu(top->norandommap);
	o->softrandommap = le32_to_cpu(top->softrandommap);
	o->bs_unaligned = le32_to_cpu(top->bs_unaligned);
	o->fsync_on_close = le32_to_cpu(top->fsync_on_close);
	o->random_distribution = le32_to_cpu(top->random_distribution);
	o->zipf_theta.u.f = fio_uint64_to_double(le64_to_cpu(top->zipf_theta.u.i));
	o->pareto_h.u.f = fio_uint64_to_double(le64_to_cpu(top->pareto_h.u.i));
	o->random_generator = le32_to_cpu(top->random_generator);
	o->hugepage_size = le32_to_cpu(top->hugepage_size);
	o->rw_min_bs = le32_to_cpu(top->rw_min_bs);
	o->thinktime = le32_to_cpu(top->thinktime);
	o->thinktime_spin = le32_to_cpu(top->thinktime_spin);
	o->thinktime_blocks = le32_to_cpu(top->thinktime_blocks);
	o->fsync_blocks = le32_to_cpu(top->fsync_blocks);
	o->fdatasync_blocks = le32_to_cpu(top->fdatasync_blocks);
	o->barrier_blocks = le32_to_cpu(top->barrier_blocks);

	o->verify_backlog = le64_to_cpu(top->verify_backlog);
	o->start_delay = le64_to_cpu(top->start_delay);
	o->timeout = le64_to_cpu(top->timeout);
	o->ramp_time = le64_to_cpu(top->ramp_time);
	o->zone_range = le64_to_cpu(top->zone_range);
	o->zone_size = le64_to_cpu(top->zone_size);
	o->zone_skip = le64_to_cpu(top->zone_skip);
	o->lockmem = le64_to_cpu(top->lockmem);
	o->offset_increment = le64_to_cpu(top->offset_increment);

	o->overwrite = le32_to_cpu(top->overwrite);
	o->bw_avg_time = le32_to_cpu(top->bw_avg_time);
	o->iops_avg_time = le32_to_cpu(top->iops_avg_time);
	o->loops = le32_to_cpu(top->loops);
	o->mem_type = le32_to_cpu(top->mem_type);
	o->mem_align = le32_to_cpu(top->mem_align);
	o->max_latency = le32_to_cpu(top->max_latency);
	o->stonewall = le32_to_cpu(top->stonewall);
	o->new_group = le32_to_cpu(top->new_group);
	o->numjobs = le32_to_cpu(top->numjobs);
	o->cpumask_set = le32_to_cpu(top->cpumask_set);
	o->verify_cpumask_set = le32_to_cpu(top->verify_cpumask_set);
	o->iolog = le32_to_cpu(top->iolog);
	o->rwmixcycle = le32_to_cpu(top->rwmixcycle);
	o->nice = le32_to_cpu(top->nice);
	o->ioprio = le32_to_cpu(top->ioprio);
	o->ioprio_class = le32_to_cpu(top->ioprio_class);
	o->file_service_type = le32_to_cpu(top->file_service_type);
	o->group_reporting = le32_to_cpu(top->group_reporting);
	o->fadvise_hint = le32_to_cpu(top->fadvise_hint);
	o->fallocate_mode = le32_to_cpu(top->fallocate_mode);
	o->zero_buffers = le32_to_cpu(top->zero_buffers);
	o->refill_buffers = le32_to_cpu(top->refill_buffers);
	o->scramble_buffers = le32_to_cpu(top->scramble_buffers);
	o->time_based = le32_to_cpu(top->time_based);
	o->disable_lat = le32_to_cpu(top->disable_lat);
	o->disable_clat = le32_to_cpu(top->disable_clat);
	o->disable_slat = le32_to_cpu(top->disable_slat);
	o->disable_bw = le32_to_cpu(top->disable_bw);
	o->gtod_reduce = le32_to_cpu(top->gtod_reduce);
	o->gtod_cpu = le32_to_cpu(top->gtod_cpu);
	o->gtod_offload = le32_to_cpu(top->gtod_offload);
	o->clocksource = le32_to_cpu(top->clocksource);
	o->no_stall = le32_to_cpu(top->no_stall);
	o->trim_percentage = le32_to_cpu(top->trim_percentage);
	o->trim_batch = le32_to_cpu(top->trim_batch);
	o->trim_zero = le32_to_cpu(top->trim_zero);
	o->clat_percentiles = le32_to_cpu(top->clat_percentiles);
	o->overwrite_plist = le32_to_cpu(top->overwrite_plist);
	o->continue_on_error = le32_to_cpu(top->continue_on_error);
	o->cgroup_weight = le32_to_cpu(top->cgroup_weight);
	o->cgroup_nodelete = le32_to_cpu(top->cgroup_nodelete);
	o->uid = le32_to_cpu(top->uid);
	o->gid = le32_to_cpu(top->gid);
	o->flow_id = __le32_to_cpu(top->flow_id);
	o->flow = __le32_to_cpu(top->flow);
	o->flow_watermark = __le32_to_cpu(top->flow_watermark);
	o->flow_sleep = le32_to_cpu(top->flow_sleep);
	o->sync_file_range = le32_to_cpu(top->sync_file_range);
	o->compress_percentage = le32_to_cpu(top->compress_percentage);
	o->compress_chunk = le32_to_cpu(top->compress_chunk);

	o->trim_backlog = le64_to_cpu(top->trim_backlog);

	for (i = 0; i < FIO_IO_U_LIST_MAX_LEN; i++)
		o->percentile_list[i].u.f = fio_uint64_to_double(le64_to_cpu(top->percentile_list[i].u.i));
#if 0
	uint8_t cpumask[FIO_TOP_STR_MAX];
	uint8_t verify_cpumask[FIO_TOP_STR_MAX];
#endif
}

void convert_thread_options_to_net(struct thread_options_pack *top,
				   struct thread_options *o)
{
	int i, j;

	string_to_net(top->description, o->description);
	string_to_net(top->name, o->name);
	string_to_net(top->directory, o->directory);
	string_to_net(top->filename, o->filename);
	string_to_net(top->opendir, o->opendir);
	string_to_net(top->ioengine, o->ioengine);
	string_to_net(top->mmapfile, o->mmapfile);
	string_to_net(top->read_iolog_file, o->read_iolog_file);
	string_to_net(top->write_iolog_file, o->write_iolog_file);
	string_to_net(top->bw_log_file, o->bw_log_file);
	string_to_net(top->lat_log_file, o->lat_log_file);
	string_to_net(top->iops_log_file, o->iops_log_file);
	string_to_net(top->replay_redirect, o->replay_redirect);
	string_to_net(top->exec_prerun, o->exec_prerun);
	string_to_net(top->exec_postrun, o->exec_postrun);
	string_to_net(top->ioscheduler, o->ioscheduler);
	string_to_net(top->profile, o->profile);
	string_to_net(top->cgroup, o->cgroup);

	top->td_ddir = cpu_to_le32(o->td_ddir);
	top->rw_seq = cpu_to_le32(o->rw_seq);
	top->kb_base = cpu_to_le32(o->kb_base);
	top->ddir_seq_nr = cpu_to_le32(o->ddir_seq_nr);
	top->iodepth = cpu_to_le32(o->iodepth);
	top->iodepth_low = cpu_to_le32(o->iodepth_low);
	top->iodepth_batch = cpu_to_le32(o->iodepth_batch);
	top->iodepth_batch_complete = cpu_to_le32(o->iodepth_batch_complete);
	top->size_percent = cpu_to_le32(o->size_percent);
	top->fill_device = cpu_to_le32(o->fill_device);
	top->ratecycle = cpu_to_le32(o->ratecycle);
	top->nr_files = cpu_to_le32(o->nr_files);
	top->open_files = cpu_to_le32(o->open_files);
	top->file_lock_mode = cpu_to_le32(o->file_lock_mode);
	top->lockfile_batch = cpu_to_le32(o->lockfile_batch);
	top->odirect = cpu_to_le32(o->odirect);
	top->invalidate_cache = cpu_to_le32(o->invalidate_cache);
	top->create_serialize = cpu_to_le32(o->create_serialize);
	top->create_fsync = cpu_to_le32(o->create_fsync);
	top->create_on_open = cpu_to_le32(o->create_on_open);
	top->create_only = cpu_to_le32(o->create_only);
	top->end_fsync = cpu_to_le32(o->end_fsync);
	top->pre_read = cpu_to_le32(o->pre_read);
	top->sync_io = cpu_to_le32(o->sync_io);
	top->verify = cpu_to_le32(o->verify);
	top->do_verify = cpu_to_le32(o->do_verify);
	top->verifysort = cpu_to_le32(o->verifysort);
	top->verifysort_nr = cpu_to_le32(o->verifysort_nr);
	top->experimental_verify = cpu_to_le32(o->experimental_verify);
	top->verify_interval = cpu_to_le32(o->verify_interval);
	top->verify_offset = cpu_to_le32(o->verify_offset);
	top->verify_pattern_bytes = cpu_to_le32(o->verify_pattern_bytes);
	top->verify_fatal = cpu_to_le32(o->verify_fatal);
	top->verify_dump = cpu_to_le32(o->verify_dump);
	top->verify_async = cpu_to_le32(o->verify_async);
	top->verify_batch = cpu_to_le32(o->verify_batch);
	top->use_thread = cpu_to_le32(o->use_thread);
	top->unlink = cpu_to_le32(o->unlink);
	top->do_disk_util = cpu_to_le32(o->do_disk_util);
	top->override_sync = cpu_to_le32(o->override_sync);
	top->rand_repeatable = cpu_to_le32(o->rand_repeatable);
	top->use_os_rand = cpu_to_le32(o->use_os_rand);
	top->log_avg_msec = cpu_to_le32(o->log_avg_msec);
	top->norandommap = cpu_to_le32(o->norandommap);
	top->softrandommap = cpu_to_le32(o->softrandommap);
	top->bs_unaligned = cpu_to_le32(o->bs_unaligned);
	top->fsync_on_close = cpu_to_le32(o->fsync_on_close);
	top->random_distribution = cpu_to_le32(o->random_distribution);
	top->zipf_theta.u.i = __cpu_to_le64(fio_double_to_uint64(o->zipf_theta.u.f));
	top->pareto_h.u.i = __cpu_to_le64(fio_double_to_uint64(o->pareto_h.u.f));
	top->random_generator = cpu_to_le32(o->random_generator);
	top->hugepage_size = cpu_to_le32(o->hugepage_size);
	top->rw_min_bs = cpu_to_le32(o->rw_min_bs);
	top->thinktime = cpu_to_le32(o->thinktime);
	top->thinktime_spin = cpu_to_le32(o->thinktime_spin);
	top->thinktime_blocks = cpu_to_le32(o->thinktime_blocks);
	top->fsync_blocks = cpu_to_le32(o->fsync_blocks);
	top->fdatasync_blocks = cpu_to_le32(o->fdatasync_blocks);
	top->barrier_blocks = cpu_to_le32(o->barrier_blocks);
	top->overwrite = cpu_to_le32(o->overwrite);
	top->bw_avg_time = cpu_to_le32(o->bw_avg_time);
	top->iops_avg_time = cpu_to_le32(o->iops_avg_time);
	top->loops = cpu_to_le32(o->loops);
	top->mem_type = cpu_to_le32(o->mem_type);
	top->mem_align = cpu_to_le32(o->mem_align);
	top->max_latency = cpu_to_le32(o->max_latency);
	top->stonewall = cpu_to_le32(o->stonewall);
	top->new_group = cpu_to_le32(o->new_group);
	top->numjobs = cpu_to_le32(o->numjobs);
	top->cpumask_set = cpu_to_le32(o->cpumask_set);
	top->verify_cpumask_set = cpu_to_le32(o->verify_cpumask_set);
	top->iolog = cpu_to_le32(o->iolog);
	top->rwmixcycle = cpu_to_le32(o->rwmixcycle);
	top->nice = cpu_to_le32(o->nice);
	top->ioprio = cpu_to_le32(o->ioprio);
	top->ioprio_class = cpu_to_le32(o->ioprio_class);
	top->file_service_type = cpu_to_le32(o->file_service_type);
	top->group_reporting = cpu_to_le32(o->group_reporting);
	top->fadvise_hint = cpu_to_le32(o->fadvise_hint);
	top->fallocate_mode = cpu_to_le32(o->fallocate_mode);
	top->zero_buffers = cpu_to_le32(o->zero_buffers);
	top->refill_buffers = cpu_to_le32(o->refill_buffers);
	top->scramble_buffers = cpu_to_le32(o->scramble_buffers);
	top->time_based = cpu_to_le32(o->time_based);
	top->disable_lat = cpu_to_le32(o->disable_lat);
	top->disable_clat = cpu_to_le32(o->disable_clat);
	top->disable_slat = cpu_to_le32(o->disable_slat);
	top->disable_bw = cpu_to_le32(o->disable_bw);
	top->gtod_reduce = cpu_to_le32(o->gtod_reduce);
	top->gtod_cpu = cpu_to_le32(o->gtod_cpu);
	top->gtod_offload = cpu_to_le32(o->gtod_offload);
	top->clocksource = cpu_to_le32(o->clocksource);
	top->no_stall = cpu_to_le32(o->no_stall);
	top->trim_percentage = cpu_to_le32(o->trim_percentage);
	top->trim_batch = cpu_to_le32(o->trim_batch);
	top->trim_zero = cpu_to_le32(o->trim_zero);
	top->clat_percentiles = cpu_to_le32(o->clat_percentiles);
	top->overwrite_plist = cpu_to_le32(o->overwrite_plist);
	top->continue_on_error = cpu_to_le32(o->continue_on_error);
	top->cgroup_weight = cpu_to_le32(o->cgroup_weight);
	top->cgroup_nodelete = cpu_to_le32(o->cgroup_nodelete);
	top->uid = cpu_to_le32(o->uid);
	top->gid = cpu_to_le32(o->gid);
	top->flow_id = __cpu_to_le32(o->flow_id);
	top->flow = __cpu_to_le32(o->flow);
	top->flow_watermark = __cpu_to_le32(o->flow_watermark);
	top->flow_sleep = cpu_to_le32(o->flow_sleep);
	top->sync_file_range = cpu_to_le32(o->sync_file_range);
	top->compress_percentage = cpu_to_le32(o->compress_percentage);
	top->compress_chunk = cpu_to_le32(o->compress_chunk);

	for (i = 0; i < DDIR_RWDIR_CNT; i++) {
		top->bs[i] = cpu_to_le32(o->bs[i]);
		top->ba[i] = cpu_to_le32(o->ba[i]);
		top->min_bs[i] = cpu_to_le32(o->min_bs[i]);
		top->max_bs[i] = cpu_to_le32(o->max_bs[i]);
		top->bssplit_nr[i] = cpu_to_le32(o->bssplit_nr[i]);

		if (o->bssplit_nr[i]) {
			unsigned int bssplit_nr = o->bssplit_nr[i];

			if (bssplit_nr > BSSPLIT_MAX) {
				log_err("fio: BSSPLIT_MAX is too small\n");
				bssplit_nr = BSSPLIT_MAX;
			}
			for (j = 0; j < bssplit_nr; j++) {
				top->bssplit[i][j].bs = cpu_to_le32(o->bssplit[i][j].bs);
				top->bssplit[i][j].perc = cpu_to_le32(o->bssplit[i][j].perc);
			}
		}

		top->rwmix[i] = cpu_to_le32(o->rwmix[i]);
		top->rate[i] = cpu_to_le32(o->rate[i]);
		top->ratemin[i] = cpu_to_le32(o->ratemin[i]);
		top->rate_iops[i] = cpu_to_le32(o->rate_iops[i]);
		top->rate_iops_min[i] = cpu_to_le32(o->rate_iops_min[i]);
	}

	memcpy(top->verify_pattern, o->verify_pattern, MAX_PATTERN_SIZE);

	top->size = __cpu_to_le64(o->size);
	top->verify_backlog = __cpu_to_le64(o->verify_backlog);
	top->start_delay = __cpu_to_le64(o->start_delay);
	top->timeout = __cpu_to_le64(o->timeout);
	top->ramp_time = __cpu_to_le64(o->ramp_time);
	top->zone_range = __cpu_to_le64(o->zone_range);
	top->zone_size = __cpu_to_le64(o->zone_size);
	top->zone_skip = __cpu_to_le64(o->zone_skip);
	top->lockmem = __cpu_to_le64(o->lockmem);
	top->ddir_seq_add = __cpu_to_le64(o->ddir_seq_add);
	top->file_size_low = __cpu_to_le64(o->file_size_low);
	top->file_size_high = __cpu_to_le64(o->file_size_high);
	top->start_offset = __cpu_to_le64(o->start_offset);
	top->trim_backlog = __cpu_to_le64(o->trim_backlog);
	top->offset_increment = __cpu_to_le64(o->offset_increment);

	for (i = 0; i < FIO_IO_U_LIST_MAX_LEN; i++)
		top->percentile_list[i].u.i = __cpu_to_le64(fio_double_to_uint64(o->percentile_list[i].u.f));
#if 0
	uint8_t cpumask[FIO_TOP_STR_MAX];
	uint8_t verify_cpumask[FIO_TOP_STR_MAX];
#endif

}

/*
 * Basic conversion test. We'd really need to fill in more of the options
 * to have a thorough test. Even better, we should auto-generate the
 * converter functions...
 */
int fio_test_cconv(struct thread_options *__o)
{
	struct thread_options o;
	struct thread_options_pack top1, top2;

	memset(&top1, 0, sizeof(top1));
	memset(&top2, 0, sizeof(top2));

	convert_thread_options_to_net(&top1, __o);
	memset(&o, 0, sizeof(o));
	convert_thread_options_to_cpu(&o, &top1);
	convert_thread_options_to_net(&top2, &o);

	return memcmp(&top1, &top2, sizeof(top1));
}
