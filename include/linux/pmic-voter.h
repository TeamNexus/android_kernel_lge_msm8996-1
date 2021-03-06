/* Copyright (c) 2015-2017 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __PMIC_VOTER_H
#define __PMIC_VOTER_H

#include <linux/mutex.h>

struct votable;
struct device;

enum votable_type {
	VOTE_MIN,
	VOTE_MAX,
	VOTE_SET_ANY,
	NUM_VOTABLE_TYPES,
};

bool is_client_vote_enabled(struct votable *votable, const char *client_str);
bool is_client_vote_enabled_locked(struct votable *votable,
							const char *client_str);
int get_client_vote(struct votable *votable, int client_id);
int get_client_vote_locked(struct votable *votable, int client_id);
int get_client_vote_by_name(struct votable *votable, const char *client_str);
int get_client_vote_by_name_locked(struct votable *votable, const char *client_str);
int get_effective_result(struct votable *votable);
int get_effective_result_locked(struct votable *votable);
int get_effective_client_id(struct votable *votable);
int get_effective_client_id_locked(struct votable *votable);
const char *get_effective_client(struct votable *votable);
const char *get_effective_client_locked(struct votable *votable);
int vote(struct votable *votable, int client_id, bool state, int val);
int vote_by_name(struct votable *votable, const char *client_str, bool state, int val);
int rerun_election(struct votable *votable);
struct votable *find_votable(const char *name);
struct votable *create_votable(struct device *dev, const char *name,
					int votable_type,
					int num_clients,
#ifdef CONFIG_LGE_PM
					int effective_result,
#endif
					int default_result,
					int (*callback)(struct device *dev,
							int effective_result,
							int effective_client,
							int last_result,
							int last_client)
					);
void destroy_votable(struct votable *votable);
void lock_votable(struct votable *votable);
void unlock_votable(struct votable *votable);

#endif /* __PMIC_VOTER_H */
