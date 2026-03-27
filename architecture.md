El programa se estructura de la siguiente manera:
defino dos estructuras, una t_data que contiene toda la información cmún a los filósofos y sus rutinas.
La otra estructura t_philo contiene la información específica de cada philosopho tal como ID y last_meal.
una funcion monitor que chequea todos los estados y corrobora si los philosofos siguen vivos para cumplir la rutina. 
La voy a llamar Hecate por la diosa de tres cabezas. REcibe la información de las estructuras t_data, t_philo y tiempo de muerte. 
Chequea que el tiempo de cada philo sea menor a die_time y permite seguir o finaliza el proceso si corresponde.

el usuario ingresa como input el número de filósofos, tiempo de muerte, tiempo de comida, tiempo de dormir y la cantidad de comidas

[input]->[parsing]->[inicializa t_data] -> [mutex]
                 ||
			  [routine]
			  	 ||
			  [hecate] -> si time < time_die -> [routine]
			  -> si time == time_die -> morir prolijamente.
