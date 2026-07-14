#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int m_nFigure[7][8] =	{
						{0,+1,	0, 0,	0, -1,	 0,-2},
						{0,-1,	0, 0,	0,+1,	-2,+1},
						{0,-1,	0, 0,	0,+1,	+2,+1},
						{0,-1,	0, 0,	-2,0,	-2,+1},
						{0,-1,	0, 0,	+2,0,	+2,+1},
						{0,-1,	0, 0,	-2,0,	 0,+1},
						{0,-1,	0, 0,	+2,0,	 0,+1}
						};

int m_nRightRotate[13][2] =	{			{+4,+2},
							{+4, 0},	{+2,+1},	{ 0,+2},
				{+4,-2},	{+2,-1},	{ 0, 0},	{-2,+1},	{-4,+2},
							{ 0,-2},	{-2,-1},	{-4, 0},
										{-4,-2}};

int m_nRightRotateTrg[13][2] = {		{0, -2},
							{-2, -1},	{0, -1},	{2, -1},
				{-4, 0},	{-2,  0},	{0,  0},	{2,  0},	{4, 0},
							{-2,  1},	{0,  1},	{2,  1},
										{0,  2}};

void main()
{
	FILE*	hFile=NULL;

	hFile=fopen("Tetris.dat", "wb");

	fwrite(m_nFigure, sizeof(int)*7*8, 1, hFile);

	fwrite(m_nRightRotate, sizeof(int)*13*2, 1, hFile);
	
	fwrite(m_nRightRotateTrg, sizeof(int)*13*2, 1, hFile);

	fclose(hFile);
}