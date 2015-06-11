/* libdogma
 * Copyright (C) 2013 Romain "Artefact2" Dalmaso <artefact2@gmail.com>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef _DOGMA_EXTRA_H
#define _DOGMA_EXTRA_H 1

#include <dogma.h>

/* -------- Rationale -------- */

/* This header contains methods which arguably may or may not belong
 * in a true dogma engine. Most of the methods below were made for
 * speed concerns or for ease of use in applications. Whether you make
 * use of them or not is your choice. */





/* -------- Data types -------- */

#define DOGMA_AFFECTOR_PENALIZED (1 << 0)
#define DOGMA_AFFECTOR_SINGLETON (1 << 1)

struct dogma_simple_affector_s {
	dogma_typeid_t id; /* typeid of the affector */
	dogma_attributeid_t destid; /* attributeid of the affected
	                             * attribute */

	double value;
	char operator; /* '=', '+', '-' or '*' depending on operation */

	uint8_t order; /* When computing the final value, these operations
	                * are applied by ascending order */
	uint8_t flags;  /* An OR'd list of DOGMA_AFFECTOR_* constants */
};
typedef struct dogma_simple_affector_s dogma_simple_affector_t;

struct dogma_simple_capacitor_s {
	dogma_context_t* context;
	double capacity;
	double delta; /* Average energy usage at peak recharge time (GJ/ms) */
	bool stable;

	union {
		double stable_fraction; /* Between 0 and 1 */
		double depletion_time; /* Time in milliseconds */
	};
};
typedef struct dogma_simple_capacitor_s dogma_simple_capacitor_t;





/* -------- Utility functions -------- */

/* Get a list of all affectors of a certain location. You MUST call
 * dogma_free_affector_list() after you are done using the list. */
int dogma_get_affectors(dogma_context_t*, dogma_location_t, dogma_simple_affector_t**, size_t*);

/* Free the list of affectors generated by dogma_get_affectors(). */
int dogma_free_affector_list(dogma_simple_affector_t*);



/* Checks if a certain type has an effect. */
int dogma_type_has_effect(dogma_typeid_t, dogma_state_t, dogma_effectid_t, bool*);

/* Checks if a certain type has effects only enabled in the active
 * state or higher. */
int dogma_type_has_active_effects(dogma_typeid_t, bool*);

/* Checks if a certain type has effects only enabled in the
 * overloaded state or higher. */
int dogma_type_has_overload_effects(dogma_typeid_t, bool*);

/* Checks if a certain type has effects which affect the target
 * ship. */
int dogma_type_has_projectable_effects(dogma_typeid_t, bool*);

/* Get the base (ie without any modifiers) value of a type
 * attribute. */
int dogma_type_base_attribute(dogma_typeid_t, dogma_attributeid_t, double*);



/* Get the number of full cycles a module can do before having to
 * reload. Uses -1 to indicate that the module never has to reload (ie
 * infinite number of cycles). */
int dogma_get_number_of_module_cycles_before_reload(dogma_context_t*, dogma_key_t, int*);



/* Run a simulation of the capacitor levels of the supplied context
 * and its targets and targeters. Use dogma_free_capacitor_list() when
 * you are done with the results. */
int dogma_get_capacitor_all(dogma_context_t*, bool include_reload_time, dogma_simple_capacitor_t**, size_t*);

/* Free the list of capacitor levels generated by
 * dogma_get_capacitor_all(). */
int dogma_free_capacitor_list(dogma_simple_capacitor_t*);

/* @deprecated */
int dogma_get_capacitor(dogma_context_t*, bool include_reload_time, double* delta, bool* stable, double*);



/* Get the n-th (starting from 0) effect ID of a location with at
 * least one non-null attribute. Returns DOGMA_NOT_FOUND if there is
 * none. */
int dogma_get_nth_type_effect_with_attributes(dogma_typeid_t, unsigned int n, dogma_effectid_t*);

/* Get the attributes of an effect of a location. */
int dogma_get_location_effect_attributes(dogma_context_t*, dogma_location_t, dogma_effectid_t,
                                         double* duration, double* trackingspeed, double* discharge,
                                         double* range, double* falloff, double* fittingusagechance);




#endif
