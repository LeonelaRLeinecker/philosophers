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

PASO 5️⃣: Monitor Hecate - Guía Conceptual
¿QUÉ ES HECATE?
Es una función que corre en un thread separado y actúa como vigilante. Mientras los filósofos comen/duermen/piensan, Hecate está constantemente verificando:

¿Alguien está muerto de hambre?
¿Todos comieron suficientes veces (si aplica)?
RESPONSABILIDADES DE HECATE:
1️⃣ VERIFICAR MUERTE POR INANICIÓN
Hecate debe chequear cada filósofo y calcular:

Si es VERDADERO → El filósofo MURIÓ
Si es FALSO → El filósofo sigue vivo
2️⃣ ACTIVAR BANDERA DE OPERACIÓN TERMINADA
Si detecta muerte O todos comieron suficientes veces:

Esta bandera hace que:

Todos los filósofos salgan de su loop while (!data->someone_die)
El thread monitor se detiene
El programa finaliza limpiamente
3️⃣ PROTEGER CON MUTEX
Hecate accede a datos compartidos (last_meal, meals_eaten, someone_die):

Debe usar death_mutex para leer/escribir sin race conditions
Esto es crítico porque los filósofos también actualizan estas variables
4️⃣ FRECUENCIA DE CHEQUEO
Hecate NO puede dormir todo el tiempo:

Si duerme 1 segundo y el filósofo se "muere" a los 100ms, Hecate no lo detectará a tiempo
Solución: Hacer chequeos cada X milisegundos (ej: 10ms o 50ms)
LÓGICA DEL BUCLE DE HECATE:
CASOS DE TERMINACIÓN:
Caso	Acción	Resultado
Filósofo muere de hambre	someone_die = 1	Imprimir muerte, terminar
Todos comieron N veces	someone_die = 1	Imprimir éxito, terminar
Error en timestamps	Protección con mutex	No hay race conditions
PUNTOS CRÍTICOS:
⚠️ TIMESTAMP INICIAL
Todos los filósofos deben tener el mismo timestamp base:

En main(): guardar start_time = get_current_time()
Pasar a t_data
En todos los timeouts: comparar contra este base
⚠️ PRECISIÓN DE CÁLCULO
⚠️ IMPRESIÓN DE MUERTE
Cuando Hecate detecta muerte:

Activar bandera someone_die = 1 (con mutex)
Imprimir: timestamp ID died
Nadie más puede imprimir después (por la bandera)
INTEGRACIÓN CON MAIN:
Hecate es un thread más, junto a los filósofos.

PREGUNTAS PARA VERIFICAR QUE ENTIENDES:
¿Cuántas veces por segundo debe chequear Hecate?
¿Qué mutex protege last_meal?
¿Qué sucede cuando Hecate detecta muerte?
¿Por qué es importante el timestamp base (start_time) en t_data?
¿Qué hace someone_die = 1 en los otros threads?