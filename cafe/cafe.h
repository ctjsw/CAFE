#ifndef __CAFE_TREE_H__
#define __CAFE_TREE_H__

#include<family.h>
#include<gmatrix.h>
#include <chooseln_cache.h>

/*! \brief Represents a single gene family and the number of members of that family that exist in each species
*
*/
typedef struct
{
	char* id;

	/// Holds the family size of the given gene family for the given species 
	/// Ordered in the same order as the species list in the associated \ref CafeFamily
	int*  count;
	char* desc;
	int   maxlh;
	int   ref;
	double*  lambda;
	double*	 mu;
	double*	 z_membership;
	int   holder;
}CafeFamilyItem;

typedef CafeFamilyItem* pCafeFamilyItem;


typedef enum 
{
	CAFE_REPORT_TEXT = 0,
	CAFE_REPORT_HTML,
	CAFE_REPORT_PDF,
}enumCafeReport;

/****************************************************************************
 * Cafe Tree
****************************************************************************/

double cafe_get_posterior(pCafeFamily pfamily, pCafeTree pcafe, family_size_range*range, double *ML, double *MAP, double *prior_rfsize, int quiet);
extern double cafe_set_prior_rfsize_empirical(pCafeParam param);
extern pCafeTree cafe_tree_new(const char* sztree, family_size_range* range, double lambda, double mu);
extern pTreeNode cafe_tree_new_empty_node(pTree pcafe);
extern void cafe_tree_set_parameters(pCafeTree pcafe, family_size_range* range, double lambda);
extern pCafeTree cafe_tree_copy(pCafeTree psrc);
extern pCafeTree cafe_tree_split(pCafeTree pcafe, int idx );
extern void cafe_tree_free(pCafeTree pcafe);
extern void __cafe_tree_free_node(pTree ptree, pTreeNode ptnode, va_list ap);
extern void cafe_tree_string_name(pString pstr, pPhylogenyNode ptnode);
extern pString cafe_tree_string_with_lambda(pCafeTree pcafe);
extern pString cafe_tree_string_with_id(pCafeTree pcafe);
extern pString cafe_tree_string(pCafeTree pcafe);
extern pString cafe_tree_string_with_familysize_lambda(pCafeTree pcafe);
extern pString cafe_tree_string_with_familysize(pCafeTree pcafe);
extern void cafe_tree_string_print(pCafeTree pcafe);
void compute_internal_node_likelihood(pTree ptree, pTreeNode ptnode);

extern void compute_tree_likelihoods(pCafeTree pcafe);
extern double* get_likelihoods(const pCafeTree pcafe);
extern void cafe_tree_node_free_clustered_likelihoods (pCafeParam param);
extern double** cafe_tree_clustered_likelihood(pCafeTree pcafe); 
extern void cafe_tree_viterbi(pCafeTree pcafe);
extern void cafe_tree_clustered_viterbi(pCafeTree pcafe, int num_likelihoods);
extern void cafe_tree_viterbi_posterior(pCafeTree pcafe, pCafeParam param);

extern pCafeParam cafe_copy_parameters(pCafeParam psrc);
extern void cafe_free_copy_parameters(pCafeParam param);

extern double cafe_tree_mp_remark(pString str, pTree ptree, pMetapostConfig pmc, va_list ap);
extern int cafe_tree_random_familysize(pCafeTree pcafe, int rootFamilysize, pBirthDeathCacheArray cache);
void node_set_birthdeath_matrix(pCafeNode pcnode, pBirthDeathCacheArray cache, int num_lambdas);
double cafe_set_prior_rfsize_poisson_lambda(pCafeParam param, double* lambda);
double *find_poisson_lambda(pCafeParam param, pCafeFamily pfamily, int *p_num_params);
void compute_posterior(pCafeFamily pfamily, int family_index, pCafeTree pcafe, double *ML, double *MAP, double *prior_rfsize);


/****************************************************************************
 * Cafe Family
****************************************************************************/
void cafe_family_add_item(pCafeFamily pcf, pArrayList data);
extern void cafe_family_item_free(pCafeFamilyItem pitem );
extern void cafe_family_free(pCafeFamily pcf);
extern void cafe_family_set_size(pCafeFamily pcf, int idx, pCafeTree pcafe);
extern int cafe_family_set_species_index(pCafeFamily pcf, pCafeTree pcafe );
extern int cafe_family_get_species_index(pCafeFamily pcf, char* speciesname); 
extern void cafe_family_set_size_with_family(pCafeFamily pcf, int idx, pCafeTree pcafe );
extern void cafe_family_set_truesize_with_family(pCafeFamily pcf, int idx, pCafeTree pcafe );
extern void cafe_family_set_size_by_species(char* speciesname, int size, pCafeTree pcafe);
extern int cafe_family_get_index(pCafeFamily pcf, const char* szid);
extern pCafeFamilyItem cafe_family_get_family_item(pCafeFamily pcf, const char* szid );
extern void cafe_family_set_size_with_family_forced(pCafeFamily pcf, int idx, pCafeTree pcafe);
extern void cafe_family_filter( pCafeParam param );
extern int cafe_family_print_cluster_membership(pCafeParam param);
extern void cafe_family_reset_maxlh(pCafeFamily pcf);
extern void cafe_family_read_validate_species(pCafeParam param, const char* file);
extern int cafe_family_split_cvfiles_byfamily(pCafeParam param, int cv_fold);
extern void cafe_family_clean_cvfiles_byfamily(pCafeParam param, int cv_fold);
extern void cafe_family_split_cvfiles_byspecies(pCafeParam param);
extern void cafe_family_clean_cvfiles_byspecies(pCafeParam param); 
extern void cafe_family_read_query_family(pCafeParam param, const char* file);

/****************************************************************************
 * Cafe Main
****************************************************************************/

extern void cafe_log(pCafeParam param, const char* msg, ... );
extern void reset_birthdeath_cache(pCafeTree tree, int k_value, family_size_range* range);
extern double* cafe_best_lambda_by_fminsearch(pCafeParam param, int lambda_len, int k);
extern double* cafe_each_best_lambda_by_fminsearch(pCafeParam param, int lambda_len );
extern void cafe_lambda_set_default(pCafeParam param, double* lambda);

extern void cafe_free_birthdeath_cache(pCafeTree pcafe);
extern void cafe_likelihood_ratio_test(pCafeParam param, double *maximumPvalues);
void input_values_randomize(input_values *vals, int lambda_len, int mu_len, int k,
	int kfix, double max_branch_length, double *k_weights);

void initialize_leaf_likelihoods_for_viterbi(double **matrix, int num_rows, int range, int familysize, int num_cols, pErrorStruct errormodel);
void reset_k_likelihoods(pCafeNode pcnode, int k, int num_factors);

double cafe_get_clustered_posterior(pCafeParam param);

#define CAFE_VERSION "3.2"

#endif
