#import <WMF/MWKLanguageFilter.h>
#import <WMF/WMFPreferredLanguageCodesProviding.h>
@class NSManagedObjectContext;
@class MWKLanguageLink;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const WMFPreferredLanguagesDidChangeNotification;

extern NSString *const WMFAppLanguageDidChangeNotification;

// User info keys for WMFPreferredLanguagesDidChangeNotification
extern NSString *const WMFPreferredLanguagesLastChangedLanguageKey; // An MWKLanguageLink instance
extern NSString *const WMFPreferredLanguagesChangeTypeKey;          // An NSNumber containing a WMFPreferredLanguagesChangeType value

typedef NS_ENUM(NSInteger, WMFPreferredLanguagesChangeType) {
    WMFPreferredLanguagesChangeTypeAdd = 1,
    WMFPreferredLanguagesChangeTypeRemove,
    WMFPreferredLanguagesChangeTypeReorder
};

@interface MWKLanguageLinkController : NSObject <MWKLanguageFilterDataSource, WMFPreferredLanguageCodesProviding>

/// Initializes `MWKLanguageLinkController` with the `NSManagedObjectContext` used for storage
- (instancetype)initWithManagedObjectContext:(NSManagedObjectContext *)moc;

/**
 * Returns all languages of the receiver, sorted by name, minus unsupported languages.
 *
 * Observe this property to be notifified of changes to the list of languages.
 */
@property (readonly, copy, nonatomic) NSArray<MWKLanguageLink *> *allLanguages;

/**
 * Returns the user's 1st preferred language - used as the "App Language".
 */
@property (readonly, copy, nonatomic, nullable) MWKLanguageLink *appLanguage;

/**
 * Returns the user's preferred languages.
 */
@property (readonly, copy, nonatomic) NSArray<MWKLanguageLink *> *preferredLanguages;

/**
 * Returns the user's preferred site URLs.
 */
@property (readonly, copy, nonatomic) NSArray<NSURL *> *preferredSiteURLs;

/**
 * All the languages in the receiver minus @c preferredLanguages.
 */
@property (readonly, copy, nonatomic) NSArray<MWKLanguageLink *> *otherLanguages;

/**
 *  Uniquely appends a new preferred language. The new language will be the last preferred language.
 *
 *  @param language the language to append
 */
- (void)appendPreferredLanguage:(MWKLanguageLink *)language;

/**
 *  Reorders a preferred language to the index given. The language must already exist in a user's preferred languages
 *
 *  @param language the language to reorder
 *  @param newIndex the new index of the langage
 */
- (void)reorderPreferredLanguage:(MWKLanguageLink *)language toIndex:(NSInteger)newIndex;

/**
 *  Removes a preferred language.
 *
 *  @param language the language to remove
 */
- (void)removePreferredLanguage:(MWKLanguageLink *)language;

- (nullable MWKLanguageLink *)languageForContentLanguageCode:(NSString *)contentLanguageCode;

+ (void)migratePreferredLanguagesToManagedObjectContext:(NSManagedObjectContext *)moc;

@end

NS_ASSUME_NONNULL_END
