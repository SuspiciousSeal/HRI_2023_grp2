
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *
 *  The basis of this file has been automatically generated
 *  by the TeMoto action package generator. Modify this file
 *  as you wish but please note:
 *
 *    WE HIGHLIY RECOMMEND TO REFER TO THE TeMoto ACTION
 *    IMPLEMENTATION TUTORIAL IF YOU ARE UNFAMILIAR WITH
 *    THE PROCESS OF CREATING CUSTOM TeMoto ACTION PACKAGES
 *    
 *  because there are plenty of components that should not be
 *  modified or which do not make sence at the first glance.
 *
 *  See TeMoto documentation & tutorials at: 
 *    https://github.com/temoto-framework
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <class_loader/class_loader.hpp>
#include "ta_wait_for_tag/temoto_action.h"

/* 
 * ACTION IMPLEMENTATION of TaWaitForTag 
 */
class TaWaitForTag : public TemotoAction
{
public:

/*
 * Function that gets invoked only once (when the action is initialized) throughout the action's lifecycle
 */
void initializeTemotoAction()
{
  /* * * * * * * * * * * * * * * * * * * * * * *
   *                          
   * ===> YOUR INITIALIZATION ROUTINES HERE <===
   *                          
   * * * * * * * * * * * * * * * * * * * * * * */

  TEMOTO_INFO_STREAM("Action initialized");
}

/*
 * Function that gets invoked when the action is executed (REQUIRED)
 */
void executeTemotoAction()
{
  getInputParameters();
  
  /* * * * * * * * * * * * * * * * * * * * * * *
   *                          
   *         ===> YOUR CODE HERE <===
   *                          
   * * * * * * * * * * * * * * * * * * * * * * */

  setOutputParameters();
}

// Destructor
~TaWaitForTag()
{
  TEMOTO_INFO("Action instance destructed");
}

// Loads in the input parameters
void getInputParameters()
{
  in_param_tag_id = GET_PARAMETER("tag_id", double);
}

// Sets the output parameters which can be passed to other actions
void setOutputParameters()
{
  SET_PARAMETER("tag_confirmed", "number", out_param_tag_confirmed);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * Class members
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Declaration of input parameters
double in_param_tag_id;

// Declaration of output parameters
double out_param_tag_confirmed;


}; // TaWaitForTag class

/* REQUIRED BY CLASS LOADER */
CLASS_LOADER_REGISTER_CLASS(TaWaitForTag, ActionBase);
