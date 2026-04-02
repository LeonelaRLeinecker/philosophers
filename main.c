/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleineck <lleineck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:02:31 by lleineck          #+#    #+#             */
/*   Updated: 2026/04/02 19:02:29 by lleineck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		error_exit("Wrong argument. You must type number of philosophers, time to die,
			|time to eat, time to sleep and eat counts (optional)");
	if (argc == 5 || argc == 6)
	{
		
	}
		
}
