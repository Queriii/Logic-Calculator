#pragma once

#define STRING_INIT_FAILURE							0x0001
#define PROPOSITION_REQUEST_INIT_FAILURE			0x0002
#define	PARSING_FAILURE								0x0003
#define PROPOSITION_REQUEST_INVALID_PARENTHESIS		0x0004
#define PROPOSITION_REQUEST_CONVERSION_FAILURE		0x0005
#define PROPOSITION_REQUEST_TREE_CREATION_FAILURE	0x0006
#define PROPOSITION_INVALID_TRUTH_VALUES			0x0007
#define REQUEST_RECEIVAL_FAILED						0x0008
#define REQUEST_MAX_LENGTH_EXCEEDED					0x0009

void Handler(int Code);