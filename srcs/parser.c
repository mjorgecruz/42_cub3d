/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:03:25 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/07/29 16:30:20 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

enum direction
{
    North,
    South,
    West,
    East 
};

enum errmsg
{
    INPUTERR,
    MAPNAME,
    CANTOPEN,
    IVALIDMAP,
    PATHERR  
};

void ft_error(int n)
{
    if  (n == INPUTERR)
        printf("ERROR 001\nInvalid input\nUSE:[./cub3d mapname.cub]\n");
    if  (n == MAPNAME)
        printf("ERROR 002\nIncorrect map name\nUSE:[./cub3d mapname.cub]\n");
    if  (n == CANTOPEN)
        printf("ERROR\nCouldn't open file\n");
        if  (n == PATHERR)
        printf("ERROR\nCouldn't reach texture path\n");
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//                         LIBFT SHITS                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}


/*
MAP formar:    map.cub
LIBFT:         yes
MinilibX:      yes
Math lib:      ALL

EXTERNAL:   open, close, read, write,
            printf, malloc, free, perror,
            strerror, exit, gettimeofday
*/



/* MAP DETAILS 

6 possible characters:
0 for an empty space,
1 for a wall
N,S,E or W  => player’s start position orientation.

ERROR CONDITIONALS
-must be closed/surrounded by walls

ERROR\n  and any message we want to display
*/

//////////////////////////////////////////////////////////////////////
//                                                                  //
//                            STRUCTURE                             //
//                                                                  //
//////////////////////////////////////////////////////////////////////

typedef struct s_data
{
    //always positive [3] always zero 
    //missing color
    //missing textures
    //no colors
    // empty file
    // 1 at the end far from the rest
    // no spaces inside map walls
    //test all wall holes
    //textures in invalid formats
    //textures duplicated
    //player on edge
    //no player
    //multiple players
    //mapp small

    int fl_rgb;   // ou passar em hexadecimal 0XFFFFFF
    int cl_rgb;
/*texture path saved here in fd. 
if invalid what to do ? are they always present? if not what to do ?*/
    int cub_fd;
    int no_fd;
    int so_fd;
    int we_fd;
    int ea_fd;
    int **map; 
}   t_data;



//funtion to get floor and celing color;

//function to get the fd from the paths of texture orientations

//function that parses the map starting in the players position

//function that gets all the map lines of the file and fills the array acordingly


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                       USER INPUT ERRORS                          //
//                                                                  //
//////////////////////////////////////////////////////////////////////


/*
checks if the user input has a *.cub file
returning false if it does not
*/

bool ft_cubfile(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '.')
        i++;
    if (!str[i] || i == 0)
        return (false);
    if (ft_strcmp("cub", str + i + 1) == 0)
        return (true);
    return (false);
}

/*
checks the correct number of arguments
return false for invalid user inputs and prints
a error message not handling file open verifications

calls:     ft_cubfile();
*/

bool check_input(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_error(INPUTERR);
        return (false);
    }
    else if (ft_cubfile(argv[1]) != true)
    {
        ft_error(MAPNAME);
        return (false);
    }
    return (true);
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//                            OPEN MAP FILE                         //
//                                                                  //
//////////////////////////////////////////////////////////////////////

bool is_fd_invalid(int fd)
{
    if (fd < 0)
    {
        ft_error(CANTOPEN);
        return (false);
    }
    return (true);
}

void read_mapfile(t_data *data, char *filename)
{
    int fd;
    (void) data;

    fd = open(filename, O_RDONLY, 0);
    if (is_fd_invalid(fd))
        return ;
    
/*

while the file is open we go thru each line, 
first we identify each line direction "NO SO WE EA" and 
get the path for the same and use this function to fill it:  

int texture_id(char *str);          to get the direction id
we should also get the path and pass it along to the next function:

int validate_textures(t_data *data, char *path, int direction);
(in a loop until all the 4 textures are filled (can we repeat paths?) 

*/
    // Using get next line
    
    //while file is open check all the other steps and
    
    // make functions for the get textures and colors
    
    //amd fill the map
     
    close (fd);
}
//////////////////////////////////////////////////////////////////////
//                                                                  //
//                       INITIALIZE STRUCTURE                       //
//                                                                  //
//////////////////////////////////////////////////////////////////////

// void init_data(t_data *data)
// {
//     (void) data;
// }

// bool get_colors(t_data *data)
// {
//     (void) data;
// }


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                       MAP FORMAT ERRORS                          //          WIP stoped here: ....
//                                                                  //
//////////////////////////////////////////////////////////////////////


// we need to get the start of the line to identify the Direction
// is this just uppercase? or should we handle lowercase?
// can only receive srings that have something no empty ones keep that in mind
//shoud this be done in a loop with the getnext line?


int texture_id(char *str)
{
    if (ft_strmp(str, "NO"))
        return (North);
    if (ft_strmp(str, "SO"))
        return (South);
    if (ft_strmp(str, "WE"))
        return (West);
    if (ft_strmp(str, "EA"))
        return (East); 
}

// negative return for errors
int get_texture_fd(char *path)
{
    int fd;
    
    if (!path)
    {
        ft_error(PATHERR);
        return (-1);
    }
    fd = open(path, O_RDONLY, 0);
    if (is_fd_invalid(fd))
    {    
        ft_error(PATHERR);
        return (-1);
    }
    return(fd);
}

//Negative return for errors
//having the direction and the path we can fill in the values

int validate_textures(t_data *data, char *path, int direction)
{
    int fd;

    fd = get_texture_fd(path);
    if (direction == North)
    data->no_fd = fd;
    if (direction == South)
    data->so_fd = fd;
    if (direction == West)
    data->we_fd = fd;
    if (direction == East)
    data->ea_fd = fd;
    else if (fd < 0)
        return (-1);
    return (0);
}

//have to close the open ones in case any of them gets error


//////////////////////////////////////////////////////////////////////
//                                                                  //
//                                MAIN                              //
//                                                                  //
//////////////////////////////////////////////////////////////////////


int main(int argc, char **argv)
{
    printf("M: start -----------------\n");
    
    t_data data;
    
    if (check_input(argc, argv) == false)
        return (1);
    
    printf("M: checkpoint \n");
    
    read_mapfile(&data, argv[1]);
    
    printf("M: Final\n");
    return (0);
}



