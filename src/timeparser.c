/*
 * ZNC Helper
 * Copyright (C) 2009 Konrad Gräfe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1301, USA.
 */

#include "config.h"
#include "internal.h"

#include "timeparser.h"

#include <prefs.h>
#include <debug.h>

time_t get_time(gchar **message) {
	struct tm t;
	gchar *timestamp, *tmp;
	
	int read = 0;
	int year = 0;
	int month = 0;

	//if(timestamp[21] != '\0') return 0;
	
	timestamp = g_strrstr(*message, "[");
	if(!timestamp) return 0;

	read = sscanf(timestamp, "[%04d-%02d-%02d %02d:%02d:%02d]", &year, &month, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
	t.tm_isdst = (-1);
	
	t.tm_hour += purple_prefs_get_int(PLUGIN_PREFS_PREFIX "/offset");
	
	if(read != 6 || year <= 1900) return 0;
	
	t.tm_year = year - 1900;
	t.tm_mon = month - 1;

	*timestamp = '\0';
	tmp = g_strdup_printf("%s%s", g_strstrip(*message), g_strstrip(timestamp + 21));
	g_free(*message);
	*message = tmp;

	purple_debug_info(PLUGIN_STATIC_NAME, "%s\n", *message);
	
	return mktime(&t);
} 
