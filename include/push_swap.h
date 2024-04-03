/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andymalgonne <andymalgonne@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:44:48 by amalgonn          #+#    #+#             */
/*   Updated: 2024/03/23 17:51:09 by andymalgonn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int				content;
	int				index;
	int				highest;
	struct s_stack	*next;
	struct s_stack	*prev;
	struct s_stack	*nbr;
}	t_stack;

void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	dlstadd_front(t_stack **lst, t_stack *new);
t_stack	*dlstlast(t_stack *lst);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);
int		check_dup(t_stack *a);
int		check_sorted(t_stack *a);
void	error_arg(void);
void	free_list(t_stack *x);
int		check_arg(char *av, t_stack **a);
int		stack_size(t_stack *a);
void	sort_two(t_stack **a);
void	sort_three(t_stack	**a);
void	assign_index(t_stack *a);
void	pre_sort(t_stack **a, t_stack **b);
void	print(t_stack *x);


#endif