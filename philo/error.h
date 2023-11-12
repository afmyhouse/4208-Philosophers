/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:49:28 by antoda-s          #+#    #+#             */
/*   Updated: 2023/11/12 18:04:10 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* ************************************************************************** */
///	ERROR CODES
/* ************************************************************************** */
# ifndef ERROR
#  define ERROR 1
# endif
# ifndef SUCCESS
#  define SUCCESS 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif
# ifndef MALLOC_ERROR
#  define MALLOC_ERROR 10
# endif
# ifndef THREAD_ERROR
#  define THREAD_ERROR 11
# endif
# ifndef ARGS_ERROR
#  define ARGS_ERROR 52
# endif
# ifndef PROCESS_ERROR
#  define PROCESS_ERROR 53
# endif
# ifndef FORK_ERROR
#  define FORK_ERROR 54
# endif
# ifndef MUTEX_ERROR
#  define MUTEX_ERROR 55
# endif
# ifndef TIME_ERROR
#  define TIME_ERROR 57
# endif
# ifndef PHILO_ERROR
#  define PHILO_ERROR 58
# endif
# ifndef DEATH_ERROR
#  define DEATH_ERROR 59
# endif
# ifndef EAT_ERROR
#  define EAT_ERROR 60
# endif
# ifndef SLEEP_ERROR
#  define SLEEP_ERROR 61
# endif
# ifndef THINK_ERROR
#  define THINK_ERROR 62
# endif
# ifndef SEMAPHORE_ERROR
#  define SEMAPHORE_ERROR 63
# endif
# ifndef SEMAPHORE_OPEN_ERROR
#  define SEMAPHORE_OPEN_ERROR 63
# endif
# ifndef SEMAPHORE_CLOSE_ERROR
#  define SEMAPHORE_CLOSE_ERROR 64
# endif

#endif
