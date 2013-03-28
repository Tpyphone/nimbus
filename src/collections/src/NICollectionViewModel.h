//
// Copyright 2011 Jeff Verkoeyen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "NIPreprocessorMacros.h" /* for NI_WEAK */

@protocol NICollectionViewModelDelegate;


#pragma mark Sectioned Array Objects

// Classes used when creating NICollectionViewModels.
@class NICollectionViewModelFooter;  // Provides the information for a footer.

typedef enum {
  NICollectionViewModelSectionIndexNone, // Displays no section index.
  NICollectionViewModelSectionIndexDynamic, // Generates a section index from the first letters of the section titles.
  NICollectionViewModelSectionIndexAlphabetical, // Generates an alphabetical section index.
} NICollectionViewModelSectionIndex;

/**
 * A non-mutable table view model that complies to the UITableViewDataSource protocol.
 *
 * This model allows you to easily create a data source for a UITableView without having to
 * implement the UITableViewDataSource methods in your UITableViewController.
 *
 * This base class is non-mutable, much like an NSArray. You must initialize this model with
 * the contents when you create it.
 *
 *      @ingroup TableViewModels
 */
@interface NICollectionViewModel : NSObject <UICollectionViewDataSource>

#pragma mark Creating Table View Models

// Designated initializer.
- (id)initWithDelegate:(id<NICollectionViewModelDelegate>)delegate;
- (id)initWithListArray:(NSArray *)listArray delegate:(id<NICollectionViewModelDelegate>)delegate;
// Each NSString in the array starts a new section. Any other object is a new row (with exception of certain model-specific objects).
- (id)initWithSectionedArray:(NSArray *)sectionedArray delegate:(id<NICollectionViewModelDelegate>)delegate;

#pragma mark Accessing Objects

- (id)objectAtIndexPath:(NSIndexPath *)indexPath;

#pragma mark Configuration

// Immediately compiles the section index.
- (void)setSectionIndexType:(NICollectionViewModelSectionIndex)sectionIndexType showsSearch:(BOOL)showsSearch showsSummary:(BOOL)showsSummary;

@property (nonatomic, readonly, assign) NICollectionViewModelSectionIndex sectionIndexType; // Default: NICollectionViewModelSectionIndexNone
@property (nonatomic, readonly, assign) BOOL sectionIndexShowsSearch; // Default: NO
@property (nonatomic, readonly, assign) BOOL sectionIndexShowsSummary; // Default: NO

#pragma mark Creating Table View Cells

@property (nonatomic, NI_WEAK) id<NICollectionViewModelDelegate> delegate;

@end

/**
 * A protocol for NICollectionViewModel to fetch rows to be displayed for the table view.
 *
 *      @ingroup TableViewModels
 */
@protocol NICollectionViewModelDelegate <NSObject>

@required

/**
 * Fetches a table view cell at a given index path with a given object.
 *
 * The implementation of this method will generally use object to customize the cell.
 */
- (UICollectionViewCell *)collectionViewModel:(NICollectionViewModel *)collectionViewModel
                        cellForCollectionView:(UICollectionView *)collectionView
                                  atIndexPath:(NSIndexPath *)indexPath
                                   withObject:(id)object;

@end

/**
 * An object used in sectioned arrays to denote a section footer title.
 *
 * Meant to be used in a sectioned array for NICollectionViewModel.
 *
 * <h3>Example</h3>
 *
 * @code
 *  [NICollectionViewModelFooter footerWithTitle:@"Footer"]
 * @endcode
 */
@interface NICollectionViewModelFooter : NSObject

+ (id)footerWithTitle:(NSString *)title;
- (id)initWithTitle:(NSString *)title;

@property (nonatomic, copy) NSString* title;

@end

/** @name Creating Table View Models */

/**
 * Initializes a newly allocated static model with the given delegate and empty contents.
 *
 * This method can be used to create an empty model.
 *
 *      @fn NICollectionViewModel::initWithDelegate:
 */

/**
 * Initializes a newly allocated static model with the contents of a list array.
 *
 * A list array is a one-dimensional array that defines a flat list of rows. There will be
 * no sectioning of contents in any way.
 *
 * <h3>Example</h3>
 *
 * @code
 * NSArray* contents =
 * [NSArray arrayWithObjects:
 *  [NSDictionary dictionaryWithObject:@"Row 1" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 2" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 3" forKey:@"title"],
 *  nil];
 * [[NIStaticTableViewModel alloc] initWithListArray:contents delegate:self];
 * @endcode
 *
 *      @fn NICollectionViewModel::initWithListArray:delegate:
 */

/**
 * Initializes a newly allocated static model with the contents of a sectioned array.
 *
 * A sectioned array is a one-dimensional array that defines a list of sections and each
 * section's contents. Each NSString begins a new section and any other object defines a
 * row for the current section.
 *
 * <h3>Example</h3>
 *
 * @code
 * NSArray* contents =
 * [NSArray arrayWithObjects:
 *  @"Section 1",
 *  [NSDictionary dictionaryWithObject:@"Row 1" forKey:@"title"],
 *  [NSDictionary dictionaryWithObject:@"Row 2" forKey:@"title"],
 *  @"Section 2",
 *  // This section is empty.
 *  @"Section 3",
 *  [NSDictionary dictionaryWithObject:@"Row 3" forKey:@"title"],
 *  [NICollectionViewModelFooter footerWithTitle:@"Footer"],
 *  nil];
 * [[NIStaticTableViewModel alloc] initWithSectionedArray:contents delegate:self];
 * @endcode
 *
 *      @fn NICollectionViewModel::initWithSectionedArray:delegate:
 */


/** @name Accessing Objects */

/**
 * Returns the object at the given index path.
 *
 * If no object exists at the given index path (an invalid index path, for example) then nil
 * will be returned.
 *
 *      @fn NICollectionViewModel::objectAtIndexPath:
 */


/** @name Configuration */

/**
 * Configures the model's section index properties.
 *
 * Calling this method will compile the section index depending on the index type chosen.
 *
 *      @param sectionIndexType The type of section index to display.
 *      @param showsSearch      Whether or not to show the search icon at the top of the index.
 *      @param showsSummary     Whether or not to show the summary icon at the bottom of the index.
 *      @fn NICollectionViewModel::setSectionIndexType:showsSearch:showsSummary:
 */

/**
 * The section index type.
 *
 * You will likely use NICollectionViewModelSectionIndexAlphabetical in practice.
 *
 * NICollectionViewModelSectionIndexNone by default.
 *
 *      @fn NICollectionViewModel::sectionIndexType
 */

/**
 * Whether or not the search symbol will be shown in the section index.
 *
 * NO by default.
 *
 *      @fn NICollectionViewModel::sectionIndexShowsSearch
 */

/**
 * Whether or not the summary symbol will be shown in the section index.
 *
 * NO by default.
 *
 *      @fn NICollectionViewModel::sectionIndexShowsSummary
 */


/** @name Creating Table View Cells */

/**
 * A delegate used to fetch table view cells for the data source.
 *
 *      @fn NICollectionViewModel::delegate
 */

#if NS_BLOCKS_AVAILABLE

/**
 * A block used to create a UICollectionViewCell for a given object.
 *
 *      @fn NICollectionViewModel::createCellBlock
 */

#endif // #if NS_BLOCKS_AVAILABLE