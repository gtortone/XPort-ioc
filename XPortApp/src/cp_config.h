/* cp_config.h - CP configuration library header */

/* Copyright (c) 2010, Lantronix, Inc. All rights reserved. */

/*
modification history
--------------------
01a,05aug08,nss  written.
*/

#ifndef _CP_CONFIG_H
#define _CP_CONFIG_H

/* CP configuration table */
struct  cp_config_t {
	unsigned char number;		/* cp number */
	unsigned char type;		/* type 0:input 1:output */
	unsigned char state;		/* status 0:diable 1:enable */
	unsigned char invert;		/* invert */
};

/* function declarations */
extern int cp_config_init (void);
extern void cp_config_exit (void);
extern int cp_config_type_set (int number, int value);
extern int cp_config_state_set (int number, int value);
extern int cp_config_invert_set (int number, int value);
extern int cp_config_level_input (int number, int *pValue);
extern int cp_config_data_input (int number, int *pValue);
extern int cp_config_data_output (int number, int value);
extern int cp_config_read (int number, struct  cp_config_t *pTable);
#if 1	/* NSS, add */
extern int cp_config_validate (int number);
#endif
extern int cp_config_nums;
extern int cp_config_ios;

#endif	/* _CP_CONFIG_H */
