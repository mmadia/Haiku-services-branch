/*
 * Copyright 2002, Marcus Overhagen. All Rights Reserved.
 * Copyright 2009, Axel Dörfler, axeld@pinc-software.de.
 * Distributed under the terms of the MIT License.
 */
#ifndef _SERVER_INTERFACE_H_
#define _SERVER_INTERFACE_H_


#include <Entry.h>
#include <MediaDefs.h>
#include <MediaNode.h>
#include <MediaAddOn.h>


enum {
	ADDONSERVER_INSTANTIATE_DORMANT_NODE,
	SERVER_REGISTER_MEDIAADDON,
	SERVER_UNREGISTER_MEDIAADDON,
	SERVER_GET_MEDIAADDON_REF,
	SERVER_REGISTER_DORMANT_NODE,
	SERVER_GET_DORMANT_NODES,
	SERVER_GET_DORMANT_FLAVOR_INFO,
	END
};


struct xfer_server_get_dormant_flavor_info {
	media_addon_id	addon;
	int32			flavor_id;
	port_id			reply_port;
};

struct xfer_server_get_dormant_flavor_info_reply {
	status_t 		result;
	type_code		type; // the flatten type_code
	size_t 			flattened_size;
	char 			flattened_data[1];
		// a flattened dormant_flavor_info, flattened_size large
};

struct xfer_server_get_dormant_nodes {
	int32			max_count;
	bool			has_input;
	media_format	input_format;
	bool			has_output;
	media_format	output_format;
	bool			has_name;
	char			name[B_MEDIA_NAME_LENGTH + 1]; // 1 for a trailing "*"
	uint64			require_kinds;
	uint64			deny_kinds;
	port_id			reply_port;
};

struct xfer_server_get_dormant_nodes_reply {
	status_t		result;
	int32			count;
		// if count > 0, a second reply containing count dormant_node_infos
		// is send
};

struct xfer_server_register_dormant_node {
	media_addon_id	purge_id;
		// if > 0, server must first remove all dormant_flavor_infos
		// belonging to that id
	type_code		type; // the flatten type_code
	size_t 			flattened_size;
	char 			flattened_data[1];
		// a flattened dormant_flavor_info, flattened_size large
};

#endif	// _SERVER_INTERFACE_H_
