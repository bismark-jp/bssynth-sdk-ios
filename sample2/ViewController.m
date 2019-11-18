//
//  ViewController.m
//  sample2
//
//  Copyright (c) 2013 bismark LLC. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface ViewController ()
{
    int port;
    int channel;
    int programChange;
}

@property (weak, nonatomic) IBOutlet UIStepper *programChangeStepper;
@property (weak, nonatomic) IBOutlet UILabel *programChangeLabel;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    port = 0;
    channel = 0;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self sendProgramChange:(int) (self.programChangeStepper.value + 0.5)];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)noteOn:(UIButton *)sender
{
    AppDelegate *appDelegate = (AppDelegate *) [[UIApplication sharedApplication]delegate];
    appDelegate.api->setChannelMessage (appDelegate.handle, port, 0x90 + channel, 0x3C + sender.tag, 0x7F);
}

- (IBAction)noteOff:(UIButton *)sender
{
    AppDelegate *appDelegate = (AppDelegate *) [[UIApplication sharedApplication]delegate];
    appDelegate.api->setChannelMessage (appDelegate.handle, port, 0x90 + channel, 0x3C + sender.tag, 0x00);
}

- (IBAction)programChange:(UIStepper *)sender
{
    [self sendProgramChange:(int) (sender.value + 0.5)];
}

- (void)sendProgramChange:(int)program
{
    AppDelegate *appDelegate = (AppDelegate *) [[UIApplication sharedApplication]delegate];
    appDelegate.api->setChannelMessage (appDelegate.handle, port, 0xC0 + channel, program, 0x00);
    programChange = program;
    
    [self performSelector:@selector(updateProgramChange) withObject:nil afterDelay:0.05f];
}

- (void)updateProgramChange
{
    char name[64];
    AppDelegate *appDelegate = (AppDelegate *) [[UIApplication sharedApplication]delegate];
    appDelegate.api->ctrl (appDelegate.handle, BSMD_CTRL_GET_INSTRUMENT_NAME + port * 16 + channel, name, sizeof (name));
    self.programChangeLabel.text = [NSString stringWithFormat:@"#%d %@", programChange, [NSString stringWithCString:name encoding:NSASCIIStringEncoding] ];
}

@end

