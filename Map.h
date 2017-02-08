#pragma once

/*
Isto é uma array 3D de mapas.
Cada Mapa é uma array 2D.
Esta array 3D é como se fosse uma lista,ou,vamos dizer, uma caixa, onde os Mapas estão guardados.
/*
char Map[3][100][100] =
{
	{ //Map 1
		{ "##########" },
		{ "#     B  #" },
		{ "#  E E   #" },
		{ "#        #" },
		{ "#       #" },
		{ "#        #" },
		{ "#  b     #" },
		{ "#        #" },
		{ "##########" }
	},
	{ //Map 2
		{ "##################" },
		{ "#                #" },
		{ "|                #" },
		{ "#                #" },
		{ "##################" }
	},
	{ //Map 3
		{ "#################################"},
		{ "#                               #"},
		{ "#                               #" },
		{ "#                               #" },
		{ "#                               #" },
		{ "###############___###############" }

	}
};
