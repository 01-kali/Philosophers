/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:56 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:58 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* bake_cake(void* arg) {
    printf("Baking cake...\n");
    sleep(2); // Simulate time taken to bake a cake
    printf("Cake is ready!\n");
    (void)arg;
    return NULL;
}

void* make_soup(void* arg) {
    printf("Making soup...\n");
    sleep(1); // Simulate time taken to make soup
    printf("Soup is ready!\n");
    (void)arg;
    return NULL;
}

void* prepare_salad(void* arg) {
    printf("Preparing salad...\n");
    sleep(1); // Simulate time taken to prepare salad
    printf("Salad is ready!\n");
    (void)arg;
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Create threads
    pthread_create(&thread1, NULL, bake_cake, NULL);
    pthread_create(&thread2, NULL, make_soup, NULL);
    pthread_create(&thread3, NULL, prepare_salad, NULL);

    // Wait for threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    printf("%ld\n",thread1);
    printf("%ld\n",thread2);
    printf("%ld\n",thread3);
    return 0;
}

