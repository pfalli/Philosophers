/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:10:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/06/11 15:23:06 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// **mutex** In your code, the cont variable is a shared resource that's being accessed 
// by multiple threads. The mutex lock is used to ensure that only one thread can 
// increment cont at a time, preventing race conditions that could lead to incorrect results.

int cont = 0;
pthread_mutex_t lock;

void  *routine()
{
  int i;

  i = -1;
  while (++i < 100)
  {
    pthread_mutex_lock(&lock);
  	  cont++;
    pthread_mutex_unlock(&lock);
  }
  return (NULL);
}

int main()
{
  pthread_t tid1, tid2;

  pthread_mutex_init(&lock, NULL);
  pthread_create(&tid1, NULL, &routine, NULL);
  printf("1cont: %d\n", cont);
  pthread_create(&tid2, NULL, &routine, NULL);
  //sleep(1);
  printf("2cont: %d\n", cont); // garbage numbers
  
  pthread_join(tid1, NULL); // will wait that the thread will end and then printf
  printf("3cont: %d\n", cont);
  pthread_join(tid2, NULL);
  printf("4cont: %d\n", cont);
  pthread_mutex_destroy(&lock);
  printf("FINAL cont: %d\n", cont);
}
