//
//  ViewController.swift
//  sample
//
//  Copyright © 2019 bismark LLC. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var seekSlider: UISlider!
    @IBOutlet weak var reverbSwitch: UISwitch!
    @IBOutlet weak var chorusSwitch: UISwitch!

    private var timer: Timer!

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        let bssynth = BssynthPlayer.shared
        
        // reverb on
        bssynth.reverb = self.reverbSwitch.isOn

        // chorus on
        bssynth.chorus = self.chorusSwitch.isOn

        // set midi contents
        let path = Bundle.main.path(forResource: "sample", ofType: "mid")!
        bssynth.set(file: path)

        self.seekSlider.maximumValue = Float(bssynth.totalClocks())
        
        // open wave output device
        bssynth.open()
    }

    override func viewWillDisappear(_ animated: Bool) {
        super.viewWillDisappear(animated)
        BssynthPlayer.shared.close()
    }

    @IBAction func start(_ sender: Any) {
        let bssynth = BssynthPlayer.shared
        if !bssynth.isPlaying {
            bssynth.start()
            self.timer = Timer.scheduledTimer(timeInterval: 1.0, target: self, selector: #selector(ViewController.updateSlider(timer:)), userInfo: nil, repeats: true)
        }
    }

    @IBAction func stop(_ sender: Any) {
        let bssynth = BssynthPlayer.shared
        if bssynth.isPlaying {
            bssynth.stop()
            timer.invalidate()
        }
    }

    @IBAction func seek(_ sender: UISlider) {
        BssynthPlayer.shared.seek(clock: UInt(sender.value))
     }

    @IBAction func keyControl(_ sender: UIStepper) {
        BssynthPlayer.shared.key = Int(sender.value)
    }

    @IBAction func speedControl(_ sender: UIStepper) {
        BssynthPlayer.shared.speed = Int(sender.value)
    }

    @IBAction func reverb(_ sender: UISwitch) {
        BssynthPlayer.shared.reverb = sender.isOn
    }

    @IBAction func chorus(_ sender: UISwitch) {
        BssynthPlayer.shared.chorus = sender.isOn
    }

    @objc func updateSlider(timer: Timer) {
        if !self.seekSlider.isTouchInside {
            self.seekSlider.value = Float(BssynthPlayer.shared.clocks)
        }
    }

    @IBAction func bounce(_ sender: Any) {
        BssynthPlayer.shared.bounce()
    }
}
