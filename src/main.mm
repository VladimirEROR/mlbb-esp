#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

extern "C" {
    void mlbb_esp_init(void);
}

__attribute__((constructor))
static void initialize() {
    dispatch_async(dispatch_get_main_queue(), ^{
        mlbb_esp_init();
        NSLog(@"[MLBB ESP] Loaded. ESP is active.");
    });
}
