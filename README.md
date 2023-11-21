# BKT_python_gridsearch
1.	Data file needs to be sorted by skill, student, and time (in that order).  
  a.	student : unique student id  
  b.	skill : unique skill name for each skill  
  c.	time: when the question was attempted  
  d.	right : 1 (correct) and 0 (incorrect)  
3.	We’ll be using a shared c library (find_par.c file) to speed up the execution of nested for loops required for finding BKT parameters using grid search. First, create a shared library file (.so extension) using the C compiler for the “find_par.c” file.  
  a.	In terminal, navigate to the directory where find_par.c file is located.  
  b.	Create the shared library using the following command   
gcc -fPIC -shared -o find_par.so find_par.c  
  c.	This should generate a “find_par.so” file in the same directory.  
4.	The find_par.c file implements a grid search for BKT parameters where L0 and T are bounded to 0.99. S and G are bounded to 0.3. These can be easily changed in the find_par.c file. Just make sure to repeat step 2 (generate .so file) if any changes are made to the find_par.c file.  
5.	A brief description of the functions in the “bkt_parameters.ipynb” file.  
  a.	get_parmtrs_all_skills(): Takes a DataFrame (discussed in step 1) as input. Returns L0, T, S, G for each of the skills present in the DataFrame. (See step 1). The function will return BKT parameters only for skills for which there are at least 25 students who attempted at least 3 questions. This check for threshold can be changed or removed if needed.  
  b.	get_predictions(): Takes DataFrame1 (discussed in step 1)  and DataFrame 2 (BKT parameters obtained from get_parmtrs_all_skill() function) as input. Returns predicted P(learned) and P(correct) with the combined DataFrame 1 and 2. Predictions are estimated only for the skills for which we BKT parameters are provided in the DataFrame2.  
  c.	collapsed_metrics(): Takes DataFrame obtained form get_predictions() function and returns collapsed rmse, collapsed auc_roc, collapsed accuracy  
  d.	non-collapsed_metrics(): Takes DataFrame obtained form get_predictions() function and returns non-collapsed rmse, non-collapsed auc_roc, non-collapsed accuracy  
  e.	ss_nfold_crossV(): Takes a DataFrame (discussed in step 1) and n (number of folds) as inputs. Implements n-fold student stratified cross validation. Returns collapsed[rmse, auc_roc, auccary], non-collapsed[rmse, auc_roc, auccary], collapsed[rmse, auc_roc, auccary of each fold], non-collapsed[rmse, auc_roc, auccary of each fold].  
