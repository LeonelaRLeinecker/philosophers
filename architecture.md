El programa se estructura de la siguiente manera:
defino dos estructuras, una t_data que contiene toda la información cmún a los filósofos y sus rutinas.
La otra estructura t_philo contiene la información específica de cada philosopho tal como ID y last_meal.
una funcion monitor que chequea todos los estados y corrobora si los philosofos siguen vivos para cumplir la rutina. 
La voy a llamar Hecate por la diosa de tres cabezas. REcibe la información de las estructuras t_data, t_philo y tiempo de muerte. 
Chequea que el tiempo de cada philo sea menor a die_time y permite seguir o finaliza el proceso si corresponde.

el usuario ingresa como input el número de filósofos, tiempo de muerte, tiempo de comida, tiempo de dormir y la cantidad de comidas

validaciones: ✓ Entre 1 y 200 filósofos
✓ Tiempos: 1 ms a 1,000,000 ms (1000 segundos)
✓ must_eat_count positivo (si se especifica)
✓ Structs correctamente tipadas (long para timestamps)

[input]->[parsing]->[inicializa t_data] -> [mutex]
                 ||
			  [routine]
			  	 ||
			  [hecate] -> si time < time_die -> [routine]
			  -> si time == time_die -> morir prolijamente.


esto debe hacer mi main
1. Validar argc/argv
2. Inicializar t_data (parsing)
3. Inicializar mutexes
4. Inicializar filósofos
5. Crear threads para cada filósofo
6. Crear thread monitor
7. Esperar que terminen (pthread_join)
8. Limpiar memoria y mutexes


📝 PASOS A SEGUIR (Orden recomendado)
PASO 1️⃣: Corregir Parsing y Validación
Fijar las constantes 6e4 (deben ser 6 o quitar validación)
Asegurar conversión a milisegundos correcta
PASO 2️⃣: Implementar get_current_time() Correctamente
PASO 3️⃣: Implementar Funciones Destructoras
destroy_mutexes() - libera todos los mutexes
Liberar memoria de t_data->philos y t_data->forks
PASO 4️⃣: Implementar philo_routine()
PASO 5️⃣: Implementar Monitor (Hecate)
PASO 6️⃣: Implementar main()

1. Validar argc/argv2. Inicializar t_data (parsing)3. Inicializar mutexes4. Inicializar filósofos5. Crear threads para cada filósofo6. Crear thread monitor7. Esperar que terminen (pthread_join)8. Limpiar memoria y mutexes
PASO 7️⃣: Sincronización Inicial
Todos los filósofos comienzan al mismo tiempo
last_meal debe ser el timestamp inicial
