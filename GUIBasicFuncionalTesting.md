# Introduction #

This guide provides a set of steps to perform, along with simple verifications, that form a basic functional testing for the GUI.

# Test #

  * Open Application

## Disabled Menu ##

  * Check menu
    1. Verify that File -> Save As option is disabled
    1. Verify that File -> Close All option is disabled
    1. Verify that File -> Quit As option is enabled
    1. Verify that File -> Open As option is enabled
    1. Verify that all options from the View, Node and Tools elements are disabled
    1. Verify that Help -> About option is enabled

## Empty File Open ##

  * File -> Open
  * The application shows a dialog, hit OK
    1. Verify that the application displays the message "Please select a distance, location and tree files"

## Enabled Menu ##

  * Load Dataset 1 through the File -> Open option
  * Check menu
    1. Verify that all options from the File, View, Node, Tools  and About elements are enabled
    1. Verify that a row labeled "Tree1" appears on the left list

## Basic Visualization, dots and Duplicate terminals ##

  * Double click on Tree1
    1. Verify that nodes don't have dots
  * Double click on node B
    1. Verify legend Location:B Name:B
  * Double click on root
    1. Verify legend Location: No info Available Name:No info Available
  * Select Tools -> Propagate
  * A dialog is displayed, select checkbox Export deviations, select file in desktop and hit Propagate
    1. Verify that the application displays the following message "The propagation has ended. Plausibility vector is now available in the node's detail. No consensus tree is available because the input trees' terminal node names have duplicates".
    1. Verify that no consensus tree should is available in tree selection list.
    1. Verify that each node has a dot on it
  * Double click on root, a dialog is displayed
    1. Verify that the application displays a matrix with three rows and two columns. The values in the plausibility column should sum 1
  * Double click on Node C, a dialog is displayed
    1. Verify that the application displays a matrix with three rows and two columns. The values in the plausibility column should sum 1
  * Select File ->Close all, OK

## Selection and Colouring ##

  * Load Dataset 2 through the File -> Open option
  * Press Shift + Left Click on D's parent node
    1. Verify that the selected node's color changed to Red
  * Select Node -> Select ancestors
    1. Verify the selected node's parents are selected too (i.e. displayed in red)
  * Select Node -> Clear selection
    1. Verify all nodes are coloured in yellow (i.e. initial color)
  * Press Shift + Left Click on D's parent node
    1. Verify that the selected node's color changed to Red
  * Select Node -> Select descendants
    1. Verify both D terminal nodes are selected (i.e. displayed in red)
  * Select Node -> Color nodes -> Select a color
    1. Verify that the selected nodes were coloured in the selected color
  * Select File -> Close all

## Consensus Tree ##

  * Load Dataset 3 through the File -> Open option
  * Select Tools -> propagate with default options
    1. Verify that the following message is displayed "The propagation has ended. Plausibility vector is now available in the node's detail.
A consensus tree is also available."
  * Double click on Tree1
    1. Verify every node has dots on it
  * Double click on consensed tree
    1. Verify every node has dots on it
  * Double click on root: The application displays a dialog with a grid
    1. Verify that the grid has two rows and six columns
  * Double click on terminal node X
    1. Verify that the dialog displays the legend Name: X Location: A
  * Select File -> Close all

## Disjoint Terminals ##
  * Load Dataset 4 through the File -> Open option
  * Select Tools -> propagate with default options
    1. Verify that the following message is displayed "he propagation has ended. Plausibility vector is now available in the node's detail. No consensus tree is available because the input trees have disjoint terminal nodes"
    1. Verify that there is no consensus tree in the tree selection list

## Terminal Node Search ##

  * Load Dataset 7 through the File -> Open option
  * Select Tools -> propagate with default options
  * Double Click on Tree3
  * Select Node -> Search Terminal Nodes
  * Enter "C"
  * Press OK
    1. Verify that the C terminal Node is selected
  * Select Node -> Clear Selection
  * Double Click on Consensus Tree
  * Select Node -> Search Terminal Nodes
  * Enter "C"
  * Press OK
    1. Verify that the C terminal Node is selected