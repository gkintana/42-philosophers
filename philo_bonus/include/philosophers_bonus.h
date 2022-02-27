/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/27 11:42:32 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/*------------------------------- COLOR CODES -------------------------------*/
# define DEF			"\033[0m"
# define RED			"\033[0;31m"
# define RED_B			"\033[1;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define PURPLE			"\033[0;35m"
# define CYAN			"\033[0;36m"

/*------------------------ PRINT TO STANDARD OUTPUT -------------------------*/
# define ERROR			"Error!\n"
# define EXPECTED		"Philosophers Program Expects 4-5 Numeric Arguments\n"
# define EX_01			"./philo [1] [2] [3] [4] [5]\nWhere:\n"
# define EX_02			"   [1] = Number of Philosophers and Forks\n"
# define EX_03			"   [2] = Time to Die in milliseconds\n"
# define EX_04			"   [3] = Time to Eat in milliseconds\n"
# define EX_05			"   [4] = Time to Sleep in milliseconds\n"
# define EX_06			"   [5] = Number of times each Philosopher must eat\n"
# define NOTE_01		"Note: [5] is optional. If not specified, the "
# define NOTE_02		"simulation will only end when a philosopher dies.\n"
# define INVALID		"Invalid argument detected\n"

# define EVENT_TITLE	"Series of Events\n"
# define CLOCK			"🕰  "
# define MS				" ms\t"
# define FORK_1			"\t🍽️   Philosopher ["
# define FORK_2			"🍽️   Philosopher ["
# define FORK_3			"] has taken a fork\n"
# define EAT_1			"\t🍝  Philosopher ["
# define EAT_2			"🍝  Philosopher ["
# define EAT_3			"] is eating\n"
# define SLEEP_1		"🛌  Philosopher ["
# define SLEEP_2		"] is sleeping\n"
# define THINK_1		"🤔  Philosopher ["
# define THINK_2		"] is thinking\n"
# define DEATH_1		"💀  Philosopher ["
# define DEATH_2		"] died\n"

/*------------------------------ RETURN VALUES ------------------------------*/
# define SUCCESS		1
# define FAILURE		-42
# define RETURN			0

/*-------------------------------- LIBRARIES --------------------------------*/
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/*---------------------------- PROGRAM STRUCTURE ----------------------------*/
typedef struct s_philo
{
	struct s_info		*info;
	int					id;
	int					meal_count;
	size_t				last_meal;
	pid_t				process;
	pthread_t			monitor;
}						t_philo;

typedef struct s_info
{
	t_philo				philo[1000];
	int					count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meal_limit;
	size_t				time_start;
	int					terminate;
	sem_t				*event;
	sem_t				*fork;
}						t_info;

/*--------------------------- FUNCTION PROTOTYPES ---------------------------*/
int		error(int error_code);
int		check_args(int argc, char **argv);
int		ft_isdigit(int c);
int		philosopher_atoi(const char *str);

int		args_to_struct(t_info *info, int argc, char **argv);
int		init_philos(t_info *info);
size_t	compute_time(void);
void	mod_usleep(t_info *info, size_t event_time);

int		init_semaphore(t_info *info);
int		simulation(t_info *info);
void	routine(t_info *info, t_philo *philo);
void	*death_monitor(void *ptr);
void	check_time_of_last_meal(t_info *info, t_philo *philo);
void	release_and_exit(t_info *info, int exit_type);
void	wait_then_release(t_info *info);

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_itoa(int n);
void	other_events(int event, char *str, int who, size_t len);

void	print_hold_forks(char *str, int who, size_t len, size_t time);
void	print_eat(char *str, int who, size_t len, size_t time);
void	print_sleep(char *str, int who, size_t len);
void	print_think(char *str, int who, size_t len);
void	print_death(char *str, int who, size_t len);
void	print_event(t_info *info, int who, int event);

void	event_single_philo(t_info *info, t_philo *philo);
void	event_hold_forks(t_info *info, t_philo *philo);
void	event_eat(t_info *info, t_philo *philo);
void	event_sleep(t_info *info, t_philo *philo);
void	event_think(t_info *info, t_philo *philo);

#endif
