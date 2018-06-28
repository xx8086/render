//
//  ViewController.m
//  lhgl
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#import "ViewController.h"
#include "context.hpp"
#include "interface_render.hpp"

@interface ViewController ()
{
    struct ESContext _esContext;
}
@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

-(void) setupGL;
-(void) tearDownGL;
@end

@implementation ViewController
CInterfaceRender _triangle;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
//    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
//    if (!self.context){
//        NSLog(@"failed to create es context");
//    }
    
//    GLKView *glview = [[GLKView alloc] initWithFrame:CGRectMake(0, 0, 200, 250) context:self.context];
//
//    glview.drawableDepthFormat = GLKViewDrawableDepthFormat24;
//    glview.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
////
//    [self.view addSubview:glview];
    
//    GLKView *_view = (GLKView *)self.view;
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!self.context){
        NSLog(@"failed to create es context");
    }
    
    GLKView *view = (GLKView*)self.view;
    
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc]initWithTarget:self action:@selector(locationChange:)];
    pan.delaysTouchesBegan = YES;
    [self.view addGestureRecognizer:pan];
}

//改变位置
-(void)locationChange:(UIPanGestureRecognizer*)p
{
    //[[UIApplication sharedApplication] keyWindow]
    UIView *move = self.view;
    CGPoint panPoint = [p locationInView:self.view];
    if(p.state == UIGestureRecognizerStateBegan)
    {
        
    }
    else if (p.state == UIGestureRecognizerStateEnded)
    {
        //[self performSelector:@selector(changeColor) withObject:nil afterDelay:4.0];//
    }
    if(p.state == UIGestureRecognizerStateChanged)
    {
        //move.center = CGPointMake(panPoint.x, panPoint.y);
    }
    else if(p.state == UIGestureRecognizerStateEnded)
    {
        
    }
}

-(void) dealloc{
    [self tearDownGL];
    if (self.context == [EAGLContext currentContext]){
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    
    if ([self isViewLoaded] && ([[self view] window] == nil)){
        self.view = nil;
        [self tearDownGL];
        
        if (self.context == [EAGLContext currentContext]){
            [EAGLContext setCurrentContext:nil];
        }
        
        self.context = nil;
    }
}

-(void) setupGL{
    [EAGLContext setCurrentContext:self.context];
    memset(&_esContext, 0, sizeof(_esContext));
    NSString *dir = [[NSBundle mainBundle] bundlePath];
    //NSString *model_path = [[NSBundle mainBundle] pathForResource:@"boblampclean" ofType:@"md5mesh"];
    //_esContext.srcfile = [model_path cStringUsingEncoding:NSASCIIStringEncoding];
    _esContext.appdir = [dir cStringUsingEncoding:NSASCIIStringEncoding];
    _esContext.width = 240;
    _esContext.height = 320;
    _triangle.esMain(&_esContext);
}
- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    _esContext.shutdown();
}


-(void)update{
    _esContext.update();
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    _esContext.width = view.drawableWidth;
    _esContext.height = view.drawableHeight;
    _esContext.draw();
}



@end
