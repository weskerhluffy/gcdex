/*
 ============================================================================
 Name        : gcdex.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

// XXX: https://www.quora.com/profile/Surya-Kiran/Posts/A-Dance-with-Mobius-Function
// XXX: https://www.spoj.com/problems/GCDEX/
// XXX: https://math.stackexchange.com/questions/1750854/how-to-calculate-double-sum-of-gcdi-j
#if 1
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <stddef.h>
#ifndef ONLINE_JUDGE
#include <unistd.h>
#include <sys/time.h>
#endif
#include <math.h>
#include <stdint.h>
#include <ctype.h>

#ifdef CACA_COMUN_LOG
#include <execinfo.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#else
#include <time.h>
#include <stdarg.h>
#endif

#if 1
#ifndef LONG_LONG_MAX
#define LONG_LONG_MAX LONG_MAX
#endif

#ifndef ULONG_LONG_MAX
#define ULONG_LONG_MAX ULONG_MAX
#endif

#define CACA_COMUN_TAM_MAX_LINEA (16*200000)
#define CACA_LOG_MAX_TAM_CADENA 2000

#define CACA_COMUN_BUF_STATICO_TAM 1000
#define CACA_COMUN_BUF_STATICO (char[CACA_COMUN_BUF_STATICO_TAM] ) { '\0' }

#define BITCH_VECTOR_NUM_BITS (sizeof(bitch_vector) * 8)

#define CACA_COMUN_ASSERT_DUROTE 0
#define CACA_COMUN_ASSERT_SUAVECITO 1
#define CACA_COMUN_ASSERT_NIMADRES 2

#define CACA_COMUN_VALOR_INVALIDO ((tipo_dato)UINT_MAX)
#define CACA_COMUN_IDX_INVALIDO ((natural)CACA_COMUN_VALOR_INVALIDO)
#define CACA_COMUN_FUNC_STATICA static

typedef char byteme;
typedef unsigned int natural;
typedef natural tipo_dato;
typedef long long entero_largo;
typedef unsigned long long entero_largo_sin_signo;
typedef long long bitch_vector;

typedef enum BOOLEANOS {
	falso = 0, verdadero
} bool;

/*
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_SUAVECITO
 #define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_NIMADRES
 */
#define CACA_COMUN_TIPO_ASSERT CACA_COMUN_ASSERT_DUROTE

#define assert_timeout_dummy(condition) 0;

#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_DUROTE
#define assert_timeout(condition) assert(condition);
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_SUAVECITO
#define assert_timeout(condition) if(!(condition)){while(1){printf("");};abort();}
#endif
#if CACA_COMUN_TIPO_ASSERT == CACA_COMUN_ASSERT_NIMADRES
#define assert_timeout(condition) 0
#endif

#ifdef CACA_COMUN_LOG
#define caca_log_debug(formato, args...) \
		do \
		{ \
			size_t profundidad = 0; \
			void *array[CACA_LOG_MAX_TAM_CADENA]; \
 			profundidad = backtrace(array, CACA_LOG_MAX_TAM_CADENA); \
			caca_log_debug_func(formato,__FILE__, __func__, __LINE__,profundidad,##args); \
		} \
		while(0);
#else
#define caca_log_debug(formato, args...) 0;
#endif

#define caca_comun_max(x,y) ((x) < (y) ? (y) : (x))
#define caca_comun_min(x,y) ((x) < (y) ? (x) : (y))

#define caca_comun_calloc_local(tipo) (&(tipo){0})

void caca_log_debug_func(const char *format, ...);

#ifndef ONLINE_JUDGE
CACA_COMUN_FUNC_STATICA void caca_comun_current_utc_time(struct timespec *ts) {

#ifdef __MACH__
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
#ifdef CACA_COMUN_LOG
	clock_gettime(CLOCK_REALTIME, ts);
#endif
#endif

}

CACA_COMUN_FUNC_STATICA void caca_comun_timestamp(char *stime) {
	time_t ltime;
	long ms;
#ifndef ONLINE_JUDGE
	struct tm result;
	struct timespec spec;
#endif
	char parte_milisecundos[50];

	ltime = time(NULL);

#ifndef ONLINE_JUDGE
	localtime_r(&ltime, &result);
	asctime_r(&result, stime);
#endif

	*(stime + strlen(stime) - 1) = ' ';

#ifndef ONLINE_JUDGE
	caca_comun_current_utc_time(&spec);
	ms = round(spec.tv_nsec / 1.0e3);
#endif
	sprintf(parte_milisecundos, "%ld", ms);
	strcat(stime, parte_milisecundos);
}

#endif
#ifdef CACA_COMUN_LOG
void caca_log_debug_func(const char *format, ...) {

	va_list arg;
	va_list arg2;
	const char *PEDAZO_TIMESTAMP_HEADER = "tiempo: %s; ";
	const char *HEADER =
	"archivo: %s; funcion: %s; linea %d; nivel: %zd caca 8====D ";
	char formato[CACA_LOG_MAX_TAM_CADENA + sizeof(HEADER)
	+ sizeof(PEDAZO_TIMESTAMP_HEADER)] = {'\0'};
	char pedazo_timestamp[sizeof(PEDAZO_TIMESTAMP_HEADER) + 100] = {'\0'};
	char cadena_timestamp[100] = {'\0'};

	caca_comun_timestamp(cadena_timestamp);
	sprintf(pedazo_timestamp, PEDAZO_TIMESTAMP_HEADER, cadena_timestamp);

	strcpy(formato, pedazo_timestamp);
	strcat(formato, HEADER);
	strcat(formato, format);
	strcat(formato, "\n");

	va_start(arg, format);
	va_copy(arg2, arg);
	vprintf(formato, arg2);
	va_end(arg2);
	va_end(arg);
	setbuf(stdout, NULL);
}
#endif

#ifdef CACA_COMUN_LOG
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo, natural tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%1d", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(natural *arreglo,
		natural tam_arreglo, char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos, "%2u",
				*(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	int i, j;
	natural inicio_buffer_act = 0;
	for (i = 0; i < filas_tam; i++) {
		caca_comun_arreglo_a_cadena(matrix + i * columas_tam, columas_tam,
				buffer + inicio_buffer_act);
		inicio_buffer_act += strlen(buffer + inicio_buffer_act);
		buffer[inicio_buffer_act++] = '\n';
		/*		caca_log_debug("pero q mierda inicio buffer act %u %s",inicio_buffer_act,buffer);*/
	}
	return buffer;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	int i;
	char *ap_buffer = NULL;
	int characteres_escritos = 0;
#ifdef ONLINE_JUDGE
	return NULL;
#endif

	memset(buffer, 0, 100);
	ap_buffer = buffer;

	for (i = 0; i < tam_arreglo; i++) {
		characteres_escritos += sprintf(ap_buffer + characteres_escritos,
				"%llu", *(arreglo + i));
		if (i < tam_arreglo - 1) {
			*(ap_buffer + characteres_escritos++) = ',';
		}
	}
	*(ap_buffer + characteres_escritos) = '\0';
	return ap_buffer;
}
#else
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena(tipo_dato *arreglo,
		natural tam_arreglo, char *buffer) {
	return NULL;
}
CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_natural(
		natural *arreglo, natural tam_arreglo, char *buffer) {
	return NULL;
}
char *caca_comun_matrix_a_cadena(tipo_dato *matrix, natural filas_tam,
		natural columas_tam, char *buffer) {
	return NULL;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_arreglo_a_cadena_entero_largo_sin_signo(
		entero_largo_sin_signo *arreglo, entero_largo_sin_signo tam_arreglo,
		char *buffer) {
	return NULL;
}
#endif

#define caca_comun_arreglo_a_cadena_entero_largo_sin_signo_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_entero_largo_sin_signo(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_buf_local(a,a_tam) caca_comun_arreglo_a_cadena(a,a_tam,CACA_COMUN_BUF_STATICO)
#define caca_comun_arreglo_a_cadena_natural_buf_local(a,a_tam) caca_comun_arreglo_a_cadena_natural(a,a_tam,CACA_COMUN_BUF_STATICO)

CACA_COMUN_FUNC_STATICA void caca_comun_strreplace(char s[], char chr,
		char repl_chr) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] == chr) {
			s[i] = repl_chr;
		}
		i++;
	}
}

CACA_COMUN_FUNC_STATICA int caca_comun_lee_matrix_long_stdin(tipo_dato *matrix,
		int *num_filas, int *num_columnas, int num_max_filas,
		int num_max_columnas) {
	int indice_filas = 0;
	int indice_columnas = 0;
	tipo_dato numero = 0;
	char *siguiente_cadena_numero = NULL;
	char *cadena_numero_actual = NULL;
	char *linea = NULL;

	linea = calloc(CACA_COMUN_TAM_MAX_LINEA, sizeof(char));

	while (indice_filas < num_max_filas
			&& fgets(linea, CACA_COMUN_TAM_MAX_LINEA, stdin)) {
		indice_columnas = 0;
		cadena_numero_actual = linea;
		caca_comun_strreplace(linea, '\n', '\0');
		if (!strlen(linea)) {
			caca_log_debug("weird, linea vacia");
			continue;
		}
		for (siguiente_cadena_numero = linea;; siguiente_cadena_numero =
				cadena_numero_actual) {
			numero = strtol(siguiente_cadena_numero, &cadena_numero_actual, 10);
			if (cadena_numero_actual == siguiente_cadena_numero) {
				break;
			}
			*(matrix + indice_filas * num_max_columnas + indice_columnas) =
					numero;
			indice_columnas++;
		}
		if (num_columnas) {
			num_columnas[indice_filas] = indice_columnas;
		}
		indice_filas++;
		caca_log_debug("las filas son %d, con clos %d", indice_filas,
				indice_columnas);
	}

	*num_filas = indice_filas;
	free(linea);
	return 0;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_cuenta_bitchs(tipo_dato num) {
	natural bitch_cnt = 0;
	tipo_dato num_mod = 0;
	num_mod = num;
	while (num_mod) {
		num_mod &= ~(num_mod & (-num_mod));
		bitch_cnt++;
	}
	return bitch_cnt;
}

CACA_COMUN_FUNC_STATICA char caca_comun_letra_a_valor_minuscula(char letra) {
	return letra - 'a';
}

CACA_COMUN_FUNC_STATICA natural caca_comun_max_natural(natural *nums,
		natural nums_tam) {
	natural max = 0;
	int i = 0;

	for (i = 0; i < nums_tam; i++) {
		natural num_act = nums[i];
		if (num_act > max) {
			max = num_act;
		}
	}

	return max;
}

CACA_COMUN_FUNC_STATICA char *caca_comun_trimea(char *cad, natural cad_tam) {
	char c = cad[0];
	char tmp = '\0';
	natural i = 0;
	natural j = 0;

	caca_log_debug("entrada %s cad_tam %u", cad, cad_tam);
	while (j < cad_tam && cad[j] != '\0') {
		caca_log_debug("en j %u car %c", j, cad[j]);
		while (j < cad_tam && !isalpha(cad[j])) {
			caca_log_debug("brincando j %u car %c", j, cad[j]);
			j++;
		}
		caca_log_debug("aora j %u car %c", j, cad[j]);
		if (j == cad_tam) {
			caca_log_debug("q ped");
			break;
		}
		tmp = cad[i];
		cad[i] = cad[j];
		cad[j] = tmp;
		i++;
		j++;
	}
	caca_log_debug("mierda '%c'", cad[j]);

	i = 0;
	while (isalpha(cad[i++]))
		;
	caca_log_debug("salida %s", cad);
	cad[i - 1] = '\0';

	return cad;
}

#endif

#define CACA_COMUN_LIMPIA_MEM(m,s) (memset(m,0,s))
#define CACA_COMUN_LIMPIA_MEM_STATICA(m) (memset(m,0,sizeof(*(m))))

CACA_COMUN_FUNC_STATICA bool caca_comun_es_digito(char c) {
	return c >= '0' && c <= '9';
}

CACA_COMUN_FUNC_STATICA byteme caca_comun_caracter_a_num(char c) {
	return c - '0';
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_byteme(byteme *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		byteme t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA void caca_comun_invierte_arreglo_natural(natural *a,
		natural a_tam) {
	natural i = 0;
	natural j = a_tam - 1;
	while (i < j) {
		natural t = a[i];
		a[i] = a[j];
		a[j] = t;
		i++;
		j--;
	}
}

CACA_COMUN_FUNC_STATICA natural caca_comun_encuentra_minimo_natural(natural *a,
		natural a_tam) {
	natural min = CACA_COMUN_VALOR_INVALIDO;
	natural i;
	for (i = 0; i < a_tam; i++) {
		if (min > a[i]) {
			min = a[i];
		}
	}
	return min;
}

CACA_COMUN_FUNC_STATICA natural caca_comun_mcd(natural a, natural b) {
	natural r = CACA_COMUN_VALOR_INVALIDO;
	while (a && b) {
		natural tmp = b;
		b = a % b;
		a = tmp;
	}

	if (!a) {
		r = b;
	}
	if (!b) {
		r = a;
	}
	return r;
}

#define caca_comun_compara_tipo(tipo) CACA_COMUN_FUNC_STATICA int caca_comun_compara_##tipo(const void *pa, const void *pb) { \
	int r = 0; \
	tipo a = *(tipo *)pa; \
	tipo b = *(tipo *)pb; \
	if (a < b) { \
		r = -1; \
	} else { \
		if (a > b) { \
			r = 1; \
		} \
	} \
	return r; \
}

caca_comun_compara_tipo(natural)

CACA_COMUN_FUNC_STATICA natural caca_comun_encuentra_divisores(natural n,
		natural *divisores, natural divisores_tam) {
	natural divisores_cnt = 0;
	natural i = 0;
	for (i = 1; i * i < n; i++) {
		if (!(n % i)) {
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = i;
			assert_timeout(divisores_cnt < divisores_tam);
			divisores[divisores_cnt++] = n / i;
		}
	}

	if (i * i == n) {
		assert_timeout(divisores_cnt < divisores_tam);
		divisores[divisores_cnt++] = n / i;
	}
	qsort(divisores, divisores_cnt, sizeof(natural),
			caca_comun_compara_natural);
	return divisores_cnt;
}

#endif

#if 1

#define PRIMOS_NUM_MAX ((int)1E6+1)
//#define PRIMOS_NUM_MAX ((int)101)

natural primos_caca[PRIMOS_NUM_MAX + 1] = { 0 };
natural primos_caca_tam = 0;
bool primos_caca_es_primo[PRIMOS_NUM_MAX + 1] = { 0 };
typedef void (*primos_caca_primo_encontrado_cb)(natural primo,
		natural idx_primo, void *cb_ctx);
typedef void (*primos_caca_compuesto_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto_origen, void *cb_ctx);

typedef void (*primos_caca_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

typedef void (*primos_caca_no_divisible_encontrado_cb)(natural primo,
		natural idx_primo, natural compuesto, void *cb_ctx);

CACA_COMUN_FUNC_STATICA natural primos_caca_criba(natural limite,
		primos_caca_primo_encontrado_cb primo_cb,
		primos_caca_compuesto_encontrado_cb compuesto_cb,
		primos_caca_divisible_encontrado_cb divisible_encontrado_cb,
		primos_caca_no_divisible_encontrado_cb no_divisible_encontrado_cb,
		void *cb_ctx) {
	caca_log_debug("primos asta %u", limite);
	assert_timeout(limite<=PRIMOS_NUM_MAX);
	natural i, j;
	for (i = 2; i <= limite; i++) {
		primos_caca_es_primo[i] = verdadero;
	}
	for (i = 2; i <= limite; i++) {
		if (primos_caca_es_primo[i]) {
			primos_caca[primos_caca_tam++] = i;
			if (primo_cb) {
				primo_cb(i, primos_caca_tam - 1, cb_ctx);
			}
		}
		for (j = 0; j < primos_caca_tam && primos_caca[j] * i <= limite; j++) {
			primos_caca_es_primo[primos_caca[j] * i] = falso;
			if (compuesto_cb) {
				compuesto_cb(primos_caca[j], j, i, cb_ctx);
			}
			if (!(i % primos_caca[j])) {
				if (divisible_encontrado_cb) {
					divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
				break;
			} else {
				if (no_divisible_encontrado_cb) {
					no_divisible_encontrado_cb(primos_caca[j], j, i, cb_ctx);
				}
			}
		}
	}
	caca_log_debug("generados %u primos", primos_caca_tam);
	return primos_caca_tam;
}

#endif

#if 1
#define PHI_EULER_NUM_MAX PRIMOS_NUM_MAX
typedef struct phi_euler_datos {
	natural phi[PHI_EULER_NUM_MAX + 1];
} phi_euler_datos;

void phi_euler_primo_encontrado_cb(natural primo, natural idx_primo,
		void *cb_ctx) {
	phi_euler_datos *d = cb_ctx;
	d->phi[primo] = primo - 1;
	caca_log_debug("phi de %u es %u", primo, d->phi[primo]);
}

void phi_euler_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	phi_euler_datos *d = cb_ctx;
	natural nuevo_comp = compuesto * primo;
	d->phi[nuevo_comp] = primo * d->phi[compuesto];
	caca_log_debug("phi de %u es %u", nuevo_comp, d->phi[nuevo_comp]);
}

void phi_euler_no_divisible_encontrado_cb(natural primo, natural idx_primo,
		natural compuesto, void *cb_ctx) {
	phi_euler_datos *d = cb_ctx;
	natural nuevo_comp = compuesto * primo;
	d->phi[nuevo_comp] = d->phi[primo] * d->phi[compuesto];
	caca_log_debug("phi de %u es %u", nuevo_comp, d->phi[nuevo_comp]);
}
#endif

#define GCDEX_MAX_VALOR PHI_EULER_NUM_MAX
typedef struct gcdex_datos {
	entero_largo_sin_signo sumatoria_totiente[GCDEX_MAX_VALOR + 1];
	entero_largo_sin_signo valores_funcion[GCDEX_MAX_VALOR + 1];
	phi_euler_datos phi_datos;
	entero_largo_sin_signo cache[GCDEX_MAX_VALOR + 1];
} gcdex_datos;



CACA_COMUN_FUNC_STATICA entero_largo_sin_signo gcdex_calcula_valor_funcion(
		natural n) {
	return ((entero_largo_sin_signo) n * ((entero_largo_sin_signo) n - 1)) >> 1;
}

CACA_COMUN_FUNC_STATICA entero_largo_sin_signo gcdex_core(natural n,
		gcdex_datos *d) {
	natural i, la;
	entero_largo_sin_signo r = 0;
	entero_largo_sin_signo *valores_funcion = d->valores_funcion;
	entero_largo_sin_signo *sumatoria_totiente = d->sumatoria_totiente;
	if (d->cache[n]) {
		r = d->cache[n];
	} else {
		for (i = 1; i <= n; i = la + 1) {
			la = n / (n / i);
			natural ci = n / i;
			//n / x yields the same value for i <= x <= la.
			printf(
					"para i %u ci %u valor func %llu, la %u suma %llu i-1 %u suma %llu\n",
					i, ci, d->valores_funcion[ci], la,
					d->sumatoria_totiente[la], i-1, d->sumatoria_totiente[i-1]);
			r += valores_funcion[ci]
					* (sumatoria_totiente[la] - sumatoria_totiente[i - 1]);
		}
		d->cache[n] = r;
	}
	return r;
}

CACA_COMUN_FUNC_STATICA void gcdex_main() {
	natural n = 0;
	gcdex_datos *d = NULL;
	d = calloc(1, sizeof(gcdex_datos));
	assert_timeout(d);

	primos_caca_criba(GCDEX_MAX_VALOR, phi_euler_primo_encontrado_cb, NULL,
			phi_euler_divisible_encontrado_cb,
			phi_euler_no_divisible_encontrado_cb, &d->phi_datos);

	d->phi_datos.phi[1] = 1;
	for (natural i = 1; i <= GCDEX_MAX_VALOR; i++) {
		d->sumatoria_totiente[i] = (entero_largo_sin_signo) d->phi_datos.phi[i]
				+ d->sumatoria_totiente[i - 1];
		caca_log_debug("valor tot %u %llu", i, d->phi_datos.phi[i]);
		d->valores_funcion[i] = gcdex_calcula_valor_funcion(i);
		caca_log_debug("valor func %u %llu", i, d->valores_funcion[i]);
	}

	while (scanf("%u\n", &n) > 0 && n) {
		entero_largo_sin_signo r = gcdex_core(n, d);
//		entero_largo_sin_signo r = 0;
		printf("%llu\n", r);
	}
}

int main(void) {
	gcdex_main();
	return EXIT_SUCCESS;
}
